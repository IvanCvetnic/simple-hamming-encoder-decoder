#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define N 256

typedef struct oc {
    unsigned char number;
    unsigned char bit;
    struct oc *left;
    struct oc *right;
} octet;

typedef struct cd {
    char code[N]; 
} octet_code;

octet_code *codes[N];
octet *tree;

int read_table (FILE *table) {
    octet_code *new;
    int i;

    for (i = 0; i < N; ++i) {
        new = (octet_code *) malloc(sizeof(octet_code));

        if (fscanf(table, "%s", new->code) != 1) return -1;
        codes[i] = new;
    }
    return 1;
}

int create_huffman_tree (){
    octet *new, *tmp;
    int i, j;

    tree = (octet *) malloc(sizeof(octet));
    tree->left = NULL;
    tree->right = NULL;

    for (i = 0; i < N; ++i) {
        j = 0;
        tmp = tree;

        while(codes[i]->code[j] != '\0') {
            if (codes[i]->code[j] == '0') {
                if (tmp->left == NULL) {
                    new = (octet *) malloc(sizeof(octet));
                    new->bit = 0;
                    new->left = NULL;
                    new->right = NULL;
                    tmp->left = new;
                    tmp = new;
                } else {
                    tmp = tmp->left;
                }
            } else if (codes[i]->code[j] == '1') {
                if (tmp->right == NULL) {
                    new = (octet *) malloc(sizeof(octet));
                    new->bit = 1;
                    new->left = NULL;
                    new->right = NULL;
                    tmp->right = new;
                    tmp = new;
                } else {
                    tmp = tmp->right;
                }
            } else{
                return -1;
            } 
            j++;
        }

        if(tmp->right != NULL || tmp->left != NULL) return -1;
        tmp->number = i;
    }
    return 1;
}

int decode_file (FILE *input, FILE *output) {
    unsigned char buffer, byte, bit;
    int i;
    octet *tmp = tree;

    while (fread(&byte, sizeof(char), 1, input) == 1) {
        
        for (i = 7; i >= 0; i--){
            bit = (byte >> i) % 2;

            if (bit == 0) {
                if (tmp->left == NULL) return -1;
                tmp = tmp->left;
            }
            else if (bit == 1){
                if (tmp->right == NULL) return -1;
                tmp = tmp->right;
            } else return -1;

            if (tmp->left == NULL && tmp->right == NULL) {
                buffer = tmp->number;
                fwrite(&buffer, sizeof(char), 1, output);
                tmp = tree;
            }
        }
    }
    return 1;
}

int main (int argc, char **argv) {
    FILE *table, *input, *output;
    
    if (argc != 4) {
        printf ("Usage:\n\t %s [huffman_table.txt] [input_file] [output_file]\n", argv[0]);
        exit(1);
    }
    if ((table = fopen(argv[1], "r")) == NULL) {
        printf("Can not open Huffman table!\n");
        exit(1);
    }
    if ((input = fopen(argv[2], "rb")) == NULL) {
        printf("Can not open Input file!\n");
        exit(1);
    }
    if ((output = fopen(argv[3], "wb")) == NULL) {
        printf("Can not create output file!\n");
        exit(1);
    }

    if (read_table (table) == -1) {
        printf("Error in reading Huffman table.\n");
        exit(1);
    }
    if (create_huffman_tree() == -1) {
        printf("Error in creating Huffman tree.\n");
        exit(1);
    }
 
    if (decode_file (input, output) == -1) {
        printf("Error in decoding input file.\n");
        exit(1);
    }

    fclose(table);
    fclose(input);
    fclose(output);
    return 0;
}
