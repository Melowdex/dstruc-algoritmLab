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

int vglChar(element_t* x, element_t* y){
    int res = (x->data->letter > y->data->letter) ? 1 : -1;
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
    splist_t* list = spl_create();      

    tree->letter_list = spl_create();


    for (int i = 0; i < size; i++){

        element_t* data = malloc(sizeof(element_t));
        data->data = &freq_data[i];

        tree->letter_list = spl_insert_sorted(tree->letter_list, data, vglFrequentie);
        list = spl_insert_sorted(list, data, vglFrequentie);
    }
    if (size >= 2){
        element_t* node1, *node2, *new_node;
        while (1) {
        
            node1 = spl_remove_at_reference(list, spl_get_first_reference(list));
            node2 = spl_remove_at_reference(list, spl_get_first_reference(list));
    
            if (node2 == NULL){ //end of list (tree created);
                tree->root = node1;
                spl_free(&list);
                break;
            }
    
            new_node->data->frequency = node1->data->frequency + node2->data->frequency;
    
            new_node->left = node1;         //idk of ik null moet toevoegen
            node1->parent = new_node;
    
            new_node->right = node2;
            node2->parent = new_node;
    
            spl_insert_sorted(list, new_node, vglFrequentie);
        }
    }

    return tree;
}

void del_nodes(element_t* node){
    if (node->left == NULL && node->right == NULL){
        //delete node
        element_t* parent = node->parent;
        if (parent == NULL){
            free(node->data);
            free(node);
        } else{
            if (parent->left == node){
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
            free(node->data);
            free(node);

            del_nodes(parent);
        }

    } else if (node->left == NULL && node->right != NULL){    
        del_nodes(node->right);
    } else {    //always left if both options are avalible or if left != NULL
        del_nodes(node->left);
    }
}

void huf_free(huftree_t **tree){

    del_nodes((*tree)->root);

    element_t* root = (*tree)->root;

    free(&((*tree)->letter_list));
}