#include <stdio.h>
#include <stdlib.h>

//7467 for demo8.txt
#define BESTAND "demo8.txt"
#define MAX_TEAMS 10

typedef struct {
    int home_team;
    int away_team;
} game;

int read_file(int** distances, game** matches);
int check_conditions(int n, int* afstanden, game* games, int** matches_played, int i, int j, int* best_result, int** home_teams, int** away_teams);
int check_for_all_teams(int n, int** home_teams);
int solve(int n, int* afstanden, game* games, int** matches_played, int i, int* best_result, int** home_teams, int** away_teams, int** distances);
int backtrack(int n, int* afstanden, game* games);

int read_file(int** distances, game** matches){
    FILE *f = fopen(BESTAND, "r");
    if (f == NULL){
        printf("nononono file foetsie\n");
        return 0;
    }

    int n, j = 0;
    fscanf(f, "%d", &n);

    int* afstanden = (int*) malloc(n * n * sizeof(int));
    game* games = malloc((n-1) * (n) * sizeof(game));

    while(!feof(f) && j < n){
        for (int i = 0; i < n; i++){
            fscanf(f, "%d", &afstanden[(j*n)+i]);
        }  
        ++j; 
    }

    j = 0;

    while(!feof(f) && j < 2*(n-1)){
        for (int i = 0; i < (int) (n/2); i++){
            game* game = malloc(sizeof(game));
            char c;
            fscanf(f, "%d%c %d", &game->home_team, &c, &game->away_team);
            games[(j*2*(n-1))+i] = *game;
        }  
        ++j; 
    }
    
    fclose(f);

    *distances = afstanden;
    *matches = games;

    return n;
}

int check_conditions(int n, int* afstanden, game* games, int** matches_played, int i, int j, int* best_result, int** home_teams, int** away_teams){
    if (i > 0){
        int prev_team = (*home_teams)[i-1];
        if (prev_team == games[(i*2*(n-1))+j].home_team || prev_team == games[(i*2*(n-1))+j].away_team || (*away_teams)[i-1] == games[(i*2*(n-1))+j].home_team || (*away_teams)[i-1] == games[(i*2*(n-1))+j].away_team){
            return 0;
        }
    } 
    return 1;
}

int check_for_all_teams(int n, int** home_teams){
    int all_teams[n];

    for (int i = 0; i < n; i++){
        all_teams[i] = 0;
    }

    for (int i = 0; i < 2*(n-1); i++){
        all_teams[((*home_teams)[i])-1] = 1;
    }
    for (int i = 0; i < n; i++){
        if (all_teams[i] != 1){
            return 0;
        }
    }
    return 1;
}

int solve(int n, int* afstanden, game* games, int** matches_played, int i, int* best_result, int** home_teams, int** away_teams, int** distances){
    if (i == 2*(n-1)){ 
        if (check_for_all_teams(n, home_teams) == 0){
            return 0;
        }
        int sum = 0;
        for (int j = 0; j < 2*(n-1)-1; j++){
            sum += (*distances)[j];
        }
        if (sum < *best_result){
            *best_result = sum;
            for (int j = 0; j < 2*(n-1); j++){
                ((*matches_played)[j].home_team) = (*home_teams)[j];
            }
        }

        return 1;
    }

    for (int j=0; j<(int) n/2; j++){    //n/2 for the matches on a game day
        if(check_conditions(n, afstanden, games, matches_played, i, j, best_result, home_teams, away_teams)){
            //add distance to result + add team in home_teams
            (*home_teams)[i] = games[(i*2*(n-1))+j].home_team;
            (*away_teams)[i] = games[(i*2*(n-1))+j].away_team;
            if (i>0)
                (*distances)[i-1] = afstanden[((*home_teams)[i-1]-1)+(n*((*home_teams)[i]-1))];

            solve(n, afstanden, games, matches_played, i+1, best_result, home_teams, away_teams, distances);
        }
    }
}

int backtrack(int n, int* afstanden, game* games){

    int* best_result;
    *best_result = 1000000;
    int* home_teams = malloc(2*(n-1) * sizeof(int));
    int* away_teams = malloc(2*(n-1) * sizeof(int));
    int* distances = malloc((2*(n-1)-1) * sizeof(int));
    int* matches_played = malloc(2*(n-1) * sizeof(game));

    solve(n, afstanden, games, &matches_played, 0, best_result, &home_teams, &away_teams, &distances);

    free(home_teams);
    free(away_teams);
    free(distances);
    return *best_result;
}

int main(){
    int* afstanden;
    game* games;
    int n = read_file(&afstanden, &games);

    printf("best result: %d\n", backtrack(n, afstanden, games));

    free(afstanden);
    free(games);
    return 0;
}