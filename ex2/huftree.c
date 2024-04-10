#include "huftree.h"
#include "splist.h"
#define MAX_LENGTH 50

struct huftree {
    splist_t* letter_list;  //points to original list
    element_t* root;    //points to top of tree
};

int vglFrequentie(element_t* x, element_t* y){
    int res = (x->data->frequency > y->data->frequency) ? 1 : -1;
    res = (x->data->frequency == y->data->frequency) ? 0 : res;
    return res;
}

int vglChar(element_t* x, element_t* y){
    int res = (x->data->letter > y->data->letter) ? 1 : -1;
    res = (x->data->letter == y->data->letter) ? 0 : res;
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

    if (size == 0){
        tree->letter_list = NULL;
        tree->root = NULL;
        return tree;
    }

    splist_t* list = spl_create();      

    tree->letter_list = spl_create();


    for (int i = 0; i < size; i++){

        element_t* data = malloc(sizeof(element_t));
        data->data = &freq_data[i];
        data->left = NULL;
        data->right = NULL;
        data->parent = NULL;

        tree->letter_list = spl_insert_sorted(tree->letter_list, data, vglFrequentie);
        list = spl_insert_sorted(list, data, vglFrequentie);
    }
    if (size == 1){
        tree->root = spl_get_element_at_reference(tree->letter_list, spl_get_first_reference(tree->letter_list));
        element_t* node = tree->root;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        spl_free(&list);
        return tree;
    }
    element_t* node1, *node2;
    element_t* new_node;
    while (1) {
    
        node1 = spl_remove_at_reference(list, spl_get_first_reference(list));
        node2 = spl_remove_at_reference(list, spl_get_first_reference(list));

        if (node2 == NULL){ //end of list (tree created);
            node1->parent = NULL;
            tree->root = node1;
            spl_free(&list);
            return tree;
        }

        new_node = malloc(sizeof(element_t));  
        new_node->data = malloc(sizeof(new_node->data));

        new_node->data->frequency = node1->data->frequency + node2->data->frequency;

        new_node->left = node1;         
        node1->parent = new_node;

        new_node->right = node2;
        node2->parent = new_node;

        spl_insert_sorted(list, new_node, vglFrequentie);
    }

}

void del_nodes(element_t* node){

    if (node->left != NULL){
        del_nodes(node->left);
    }
    if (node->right != NULL){
        del_nodes(node->right);
    }
    //free(node->data);
    free(node);
}

void huf_free(huftree_t **tree){
    if ((*tree)->root != NULL){
        del_nodes((*tree)->root);
        spl_free(&((*tree)->letter_list));
    }
    free(*tree);
    *tree = NULL;
}

void reverse(uint8_t* array, int start, int end){
    uint8_t temp;

    while(start < end){
        temp = get_bit(array, start);

        if (get_bit(array, end) == 1){
            set_bit(array, start++);
        } else{
            clear_bit(array, start++);
        }

        if (temp == 1){
            set_bit(array, end--);
        } else{
            clear_bit(array, end--);
        }
    }
}

int huf_encode(huftree_t *tree, char* input, uint8_t* output){
    int n = 0, i = 0;

    while(*input != '\0'){
        element_t* data = malloc(sizeof(element_t));
        data->data = malloc(sizeof(freq_data_t));
        data->data->letter = *input;
        
        element_t* node = spl_get_element_at_reference(tree->letter_list, spl_get_reference_of_element(tree->letter_list, data, vglChar));
        
        free(data->data);
        free(data);
        
        if(node != NULL){
            element_t* n_node = node->parent;
            i = 0;

            while(n_node != NULL){

                if (n_node->left == node){
                    set_bit(output, n+i);
                } else{
                    clear_bit(output, n+i);
                }

                i++;
                node = n_node;
                n_node = node->parent;
            }

            reverse(output, n, n+i-1);
            n += i;
        }
        ++(input);
    }

    return n;
}

char* huf_decode(huftree_t *tree, uint8_t* code, int size){
    char result[MAX_LENGTH];
    int index = 0;

    element_t* curr_node = tree->root;

    for (int i = 0; i<size; i++){
        if (get_bit(code, i) == 1 && curr_node->left != NULL){
            curr_node = curr_node->left;
        }else if (get_bit(code, i) == 0 && curr_node->right != NULL){
            curr_node = curr_node->right;
        }else{
            result[index++] = curr_node->data->letter;
            curr_node = tree->root;
            --i;
        }
    }

    result[index++] = curr_node->data->letter; //last letter in array

    result[index] = '\0';

    char* res = malloc(index*sizeof(char));
    
    for (int i = 0; i<=index; i++){
        res[i] = result[i];
    }

    return res;
}