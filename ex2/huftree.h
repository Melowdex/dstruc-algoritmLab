#ifndef _HUFTREE_H
#define _HUFTREE_H

#include <stdint.h>
#include <string.h>

typedef struct {
    char letter;
    int frequency;
} freq_data_t;

/** huftree_t is a struct containing at least a head pointer to the start of the list; */
typedef struct huftree huftree_t;

/** Create and allocate memory for a new Huffman tree
 * \param freq_data an splist with all frequency data for any given character
 *                  all data in the list must be sorted ascendent by frequency
 * \return a pointer to a newly-allocated and initialized tree.
 */
huftree_t* huf_create(freq_data_t freq_data[], int size);

/** Deletes all elements in the Huffman tree
 * - Every list node of the list needs to be deleted. (free memory)
 * - The tree itself also needs to be deleted. (free all memory)
 * - '*tree' must be set to NULL.
 * \param list a double pointer to the list
 */
void huf_free(huftree_t **tree);

/** Encodes a given string to an output buffer using a given Huffman tree
 * \param tree a pre loaded Huffman tree
 * \param input the input text to be compressed
 * \param output a pointer to an output buffer where the compressed data will be written to
 * \return the amount of bits written to the output buffer
 */
int huf_encode(huftree_t *tree, char* input, uint8_t* output);

/** Decode a given compressed data buffer to a string using a given Huffman tree
 * \param tree a pre loaded Huffman tree
 * \param code the compressed code
 * \param size the amount of bits in the compressed code
 * \return a string pointer to the uncompressed text
 */
char* huf_decode(huftree_t *tree, uint8_t* code, int size);

#endif //_HUFTREE_H
