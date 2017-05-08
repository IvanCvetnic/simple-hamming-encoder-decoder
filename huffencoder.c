#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define N 256

typedef struct oc {
    unsigned char number;
    int freq;
    unsigned char bit;
    struct oc *left;
    struct oc *right;
    struct oc *next;
} octet;

typedef struct cd {
    char code[N]; 
} octet_code;

octet_code *codes[N];
octet *octets[N];

octet *toplist = NULL;
octet *huffman_tree = NULL;


int octets_initialization() {
    int i;
    octet *new_oct;
    octet_code *new_code;

    for (i = 0; i < N; ++i) {
        if ((new_oct = (octet *) malloc(sizeof(octet))) == NULL) return -1;
        new_oct->number = i;
        new_oct->freq = 0;
        new_oct->left = NULL;
        new_oct->right = NULL;
        new_oct->next = NULL;
        octets[i] = new_oct;
        if ((new_code = (octet_code *) malloc(sizeof(octet_code))) == NULL) return -1;
        new_code->code[0] = '\0';
        codes[i] = new_code;
    }
    return 0;
}

int compare_octets (octet *o1, octet *o2) {
    if (o2 == NULL) return -1;
    if (o1->freq > o2->freq){
        return 1;
    } else if (o1->freq < o2->freq) {
        return -1;
    } else {
        if (o1->number > o2->number) {
            return -1;
        } else if (o1->number < o2->number) {
            return 1;
        } else return -1;
    }
}

void add_to_toplist (octet *new) {
    octet *p;
    if (toplist == NULL || compare_octets(new, toplist) == -1) {
        new->next = toplist;
        toplist = new;
    }else{
        for (p = toplist; p->next && (compare_octets(new, p->next) == 1); p = p->next);
        new->next = p->next;
        p->next = new;
    }
}

octet *take_from_toplist() {
    octet *tmp;
    if (toplist == NULL) return NULL;
    tmp = toplist;
    toplist = tmp->next;
    tmp->next = NULL;
    return tmp; 
}

void sort_octets() {
    int i;
    for (i = 0; i < N; ++i) {
        add_to_toplist (octets[i]);
    }
}

void insert_to_code(octet *min, int bit){
    char tmp[N];

    if (min) {
        insert_to_code(min->left, bit);
        if (min->left == NULL && min->right == NULL) {
            if (bit == 0) {
                tmp[0] = '0';
            } else if (bit == 1) {
                tmp[0] = '1';
            } else return;
            tmp[1] = '\0';
            strcat(tmp, codes[min->number]->code);
            strcpy(codes[min->number]->code, tmp);
        }
        insert_to_code(min->right, bit);
    }
}

void huffman_algorithm(){
    octet *min1, *min2, *new;

    while (toplist->next != NULL) {
        min1 = take_from_toplist();
        min2 = take_from_toplist();

        min1->bit = 0;
        min2->bit = 1;

        insert_to_code(min1, 0);
        insert_to_code(min2, 1);

        new = (octet *) malloc(sizeof(octet));
        new->freq = min1->freq + min2->freq;
        new->number = min2->number;
        new->left = min1;
        new->right = min2;

        add_to_toplist(new);
    }
    huffman_tree = toplist;
}

void create_table (FILE *table) {
    int i;
    for (i = 0; i < N; ++i) {
        fprintf(table, "%s\n",codes[i]->code);
    }
}

int encode_file (FILE *input, FILE *output) {
    unsigned char byte;
    unsigned char buffer = 0;
    int i;
    int counter = 0;

    while (fread(&byte, sizeof(char), 1, input) == 1) {
        i = 0;
        while (codes[byte]->code[i] != '\0') {
            if (codes[byte]->code[i] == '0'){
                buffer = buffer * 2;
            } else if (codes[byte]->code[i] == '1'){
                buffer = (buffer * 2) + 1;
            }else return -1;
            counter++;
            if (counter >= 8) {
                fwrite(&buffer, sizeof(char), 1, output);
                counter = 0;
                buffer = 0;
            }
            i++;
        }
    }
    if (counter != 0) {
        for (i = counter; i < 8; ++i) {
            buffer = buffer * 2;
        }
        fwrite(&buffer, sizeof(char), 1, output);
    }
    return 1;
}

int main (int argc, char **argv) {
    FILE *input, *table, *output;
    unsigned char byte;
    
    if (argc != 4) {
        printf ("Usage:\n\t %s [input_file] [huffman_table.txt] [output_file]\n", argv[0]);
        exit(1);
    }
    if ((input = fopen(argv[1], "rb")) == NULL) {
        printf("Can not open input file!\n");
        exit(1);
    }
    if ((table = fopen(argv[2], "w+")) == NULL) {
        printf("Can not create file for Huffman table!\n");
        exit(1);
    }
    if ((output = fopen(argv[3], "wb")) == NULL) {
        printf("Can not create output file.\n");
        exit(1);
    }

    octets_initialization();
    while (fread(&byte, sizeof(char), 1, input) == 1) {
        octets[(int) byte]->freq++;
    }
    sort_octets();
    huffman_algorithm();
    create_table (table);
    fseek(input, 0L, SEEK_SET);
    encode_file(input, output);

    fclose(input);
    fclose(table);
    fclose(output);
    return 0;
}
