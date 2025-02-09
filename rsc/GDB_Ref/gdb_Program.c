#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_product(int a, int b) {
    int product = a * b;
    printf("Product: %d\n", product);
}

void print_arguments(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    print_arguments(argc, argv);
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        print_product(rand(), rand());
    }
    return 0;
}
