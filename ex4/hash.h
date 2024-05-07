#ifndef _HASH_H
#define _HASH_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HTSIZE 53
#define LEN 7

typedef struct {
    char naam[LEN + 1];
    int waarde;
    int aantal;
} ht_element;

extern ht_element tabel[HTSIZE];

/**
 * Init the 'tabel' and set all data in the elements to 0
 */
void ht_init(void);

/**
 * Print an overview of all elements in the 'tabel' on the screen
 */
void ht_print(void);

/**
 * Install a ht_element based on a string to a free spot in 'tabel'
 * @param naam the string to be installed
 * @return the index at which the string is installed
 */
int ht_install(char* naam);

/**
 * Update the 'waarde' in the ht_element struct for a given index in the 'tabel'
 * @param index the index to be updated
 * @param waarde the new value
 */
void ht_update(int index, int waarde);

#endif //_HASH_H