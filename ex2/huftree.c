#include "huftree.h"
#include "splist.h"

struct huftree {
    splist_t* letter_list;  //points to original list
    element_t* root;    //points to top of tree
};

int vglFrequentie(element_t* x, element_t* y){
    int res = (x->data->frequency > y->data->frequency) ? 1 : -1;
    res = (x->data->frequency == y->data->frequency) ? 0 : res;
    return res;
}

static void set_bit(uint8_t data[], int index){
    int i = index / 8;
    int pos = index % 8;
    uint8_t mask = 1 << pos;
    data[i] |= mask;
    // data[index/8] |= 1 << (index % 8)
}

static void clear_bit(uint8_t data[], int index){
    int i = index / 8;
    int pos = index % 8;
    uint8_t mask = ~(1 << pos);
    data[i] &= mask;
    // data[index/8] &= ~(1 << (index % 8))
}

static int get_bit(uint8_t data[], int index) {
    int i = index / 8;
    int pos = index % 8;
    uint8_t mask = 1 << pos;
    return (data[i] & mask) != 0;
    // return (data[index/8] & (1 << (index % 8))) != 0
}

huftree_t* huf_create(freq_data_t freq_data[], int size) {

    huftree_t* tree = malloc(sizeof(huftree_t));

    tree->letter_list = spl_create();

    for (int i = 0; i < size; i++){

        element_t* data = malloc(sizeof(element_t));
        data->data = &freq_data[i];

        tree->letter_list = spl_insert_sorted(tree->letter_list, data, vglFrequentie);
    }

    
}