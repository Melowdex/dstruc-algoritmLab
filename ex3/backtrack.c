#include <stdio.h>
#include <stdlib.h>

#define BESTAND "demo6.txt"
#define MAX_TEAMS 10

typedef struct {
    int home_team;
    int away_team;
} game;

int read_file(int afstanden, game *games){
    FILE *f = fopen(BESTAND, "r");
    if (f == NULL){
        printf("nononono file foetsie\n");
        return 0;
    }

    int n, j = 0;
    fscanf(f, "%d", &n);

    afstanden = (int*) malloc(n * n * sizeof(int));
    games = malloc((n-1) * (n) * sizeof(game));

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

    

    return n;
}

int main(){
    int afstanden;
    game games;
    int n = read_file(&afstanden, &games);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", afstanden[(i*n)+j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2*(n-1); i++){
        for (int j = 0; j < (int) (n/2); j++){
            printf("%d %d\n", (&games[(i*2*(n-1))+j])->home_team, (&games[(i*2*(n-1))+j])->away_team);
        }
        printf("\n");
    }

    free(&afstanden);
    free(&games);
    return 0;
}

