#include "hash.h"

int main(int argc, char *argv[]) {
    char buffer[1024];;

    ht_init();
    while (scanf("%s%*c", buffer) != EOF) {
        int index = ht_install(buffer);
        printf("[%2d] %s\n", index, buffer);
    }
    ht_print();
    return 0;
}
