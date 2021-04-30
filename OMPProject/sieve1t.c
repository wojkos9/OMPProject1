#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "getopt.h"

#define MAXPRIME 10000

#define byte unsigned char
#define log(...) fprintf(stderr, __VA_ARGS__)

int main(int argc, char* argv[]) {
    byte* tab;
    unsigned long i, j, cnt;
    int opt;
    int size = -1;

    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                size = atoi(optarg);
                break;
        }
    }

    size = size == -1 ? MAXPRIME : size;

    if (size <= 0) {
        log("Invalid size\n");
        return -1;
    }
    log("Size: %d\n", size);

    tab = (byte*)malloc(size + 1);
    memset(tab, 0, sizeof(byte) * (size + 1));

    cnt = 0;
    for (i = 2; i <= size; i++) {
        if (tab[i]) {
            continue;
        }
        cnt++; // found prime
        for (j = i; j <= size; j += i) {
            tab[j] = 1;
        }
    }

    log("Primes count: %d\n", cnt);

    free(tab);
    return 0;
}