#include "hash.h"
#include <math.h>

ht_element tabel[HTSIZE];

/**
 * Create a hash for the text based on the base26 algorithm
 * @param text the text to be hashed
 * @return the hash fo the text represented as an integer
 */
static int myBase26(char* text);

/**
 * Linear probe for a free spot in 'tabel' with max size HTSIZE
 * @param text the text to be probed
 * @return the index of a free spot in the table
 */
static int indexWithLinearProbe(char* text);

void ht_init(void) {
    memset(tabel, 0, sizeof(ht_element) * HTSIZE);
}

void ht_print(void) {
    for (int i = 0; i < HTSIZE; i++){
        if (strlen(tabel[i].naam) != 0){
            printf("naam: %s, waarde: %d, aantal: %d\n", tabel[i].naam, tabel[i].waarde, tabel[i].aantal);
        }
    }
}

int ht_install(char* naam) {
    int index = indexWithLinearProbe(naam);
    strcpy(tabel[index].naam, naam);
    return index;
}

void ht_update(int index, int waarde) {
    tabel[index].waarde = waarde;
}

static int myBase26(char* text) {

    int hash = 0;
    int l = strlen(text);
    if (l <= LEN){
        if (l > 3){
            l = (int) l/2;
        }else{
            l = 1;
        }

        for (int i = l-1; i <= l+1; i++){
            if (i < strlen(text)) {
                hash += (text[i] - 'a') * pow(26, i);
            }
        }
        return hash % HTSIZE;
    }

    return -1;
}


static int indexWithLinearProbe(char* text){
    int hash = myBase26(text);
    if (hash == -1){
        return -1;
    }

    if (strlen(tabel[hash].naam) == 0 || strcmp(tabel[hash].naam, text) == 0){
        return hash;
    }else{
        while (1){
            --hash; 
            if (strlen(tabel[hash].naam) == 0 ){
                return hash;
            } 
            if (hash == 0)
                hash = HTSIZE;
        }
    }
}