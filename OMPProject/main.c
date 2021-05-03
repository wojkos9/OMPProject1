#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#include "getopt.h"
#include "utils.h"
#include "algs.h"

#define MAXPRIME ((ulong) 1e7 )

static const char *help_str = ""
"0\tsingle-threaded naive\n"
"1\tsingle-threaded sieve\n";

int main(int argc, char* argv[]) { 
    int c;

    struct alg_options opt = {.min = 2, .max = MAXPRIME, .verbose = 0};
    algfun *algs[] = {&naive1t, &sieve1t};
    int alg_num = 1;
    algfun *fun = algs[alg_num];

    while ((c = getopt(argc, argv, "a:b:c:vh")) != -1) {
        switch (c) {
            case 'a':
                opt.min = atoi(optarg);
                break;
            case 'b':
                opt.max = atoi(optarg);
                break;
            case 'c':
                alg_num = atoi(optarg);

                if (alg_num >= 0 && alg_num < arrlen(algs)) {
                    fun = algs[alg_num];
                }
                else {
                    debug("Invalid alg index; %s\n", optarg);
                    return -1;
                }
                break;
            case 'v':
                opt.verbose += 1;
                break;
            case 'h':
                printf("%s", help_str);
                return 0;
        }
    }

    if (opt.max - opt.min < 0) {
        debug("ERR Range. 0 primes\n");
        return 0;
    }

    debug("Starting alg %d (MIN=%llu, MAX=%llu)\n", alg_num, opt.min, opt.max);
    debug("sizeof(ulong) = %d\n", sizeof(ulong));

    ulong nprimes = fun(opt);

    debug("\nPrimes count: %llu\n", nprimes);
    debug("Execution time: %lf s\n", read_timer());

    return 0;
}