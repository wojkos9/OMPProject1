#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#include "getopt.h"
#include "utils.h"
#include "algs.h"

#define MAXPRIME    49
#define MINPRIME    10
#define NUM_THREADS 8

#define LIST_PRIMES 0
#define VERBOSE_LVL 1
#define ALGS_RUN_ORDER 0,1

static const char* help_str = ""
"0\tsingle-threaded naive\n"
"1\tsingle-threaded sieve\n"
"2\tmulti-threaded sieve (domain)\n"
"3\tmulti-threaded sieve (functional)\n"
"4\tmulti-threaded naive (domain)\n";

int main(int argc, char* argv[]) { 
    int c;

    struct alg_options opt = {
        .min = MINPRIME,
        .max = MAXPRIME,
        .verbose = LIST_PRIMES,
        .num_threads = NUM_THREADS};

    int alg_cmp[] = { ALGS_RUN_ORDER };

    DEBUG_LVL = VERBOSE_LVL;

    while ((c = getopt(argc, argv, "a:b:j:vh")) != -1) {
        switch (c) {
            case 'a':
                opt.min = atoi(optarg);
                break;
            case 'b':
                opt.max = atoi(optarg);
                break;
            case 'j':
                {
                    int nt;
                    nt = atoi(optarg);
                    if (nt > 0) {
                        opt.num_threads = nt;
                    }
                    else {
                        debug(0, "Invalid number of threads; %s\n", optarg);
                        return -1;
                    }
                }
                break;
            case 'v':
                DEBUG_LVL += 1;
                break;
            case 'h':
                printf("%s", help_str);
                return 0;
        }
    }

    if (opt.max - opt.min < 0) {
        debug(0, "ERR Range. 0 primes\n");
        return 0;
    }

    debug(0, "sizeof(ulong) = %d\n", sizeof(ulong));

    for (int i = 0; i < arrlen(alg_cmp); i++) {
        int algn = alg_cmp[i];

        struct alg_t alg = ALGS_LIST[algn];

        log_prime(0); // reset print offset
        debug(0, "\n[%d] START \"%s\" (MIN=%llu, MAX=%llu, threads=%d)\n", algn, alg.name, opt.min, opt.max, opt.num_threads);

        ulong nprimes = alg.fun(opt);

        debug(1, "\n[%d] Primes count: %lld\n", algn, nprimes);
        debug(0, "[%d] Execution time: %lf s\n", algn, read_timer());
    }
    

    return 0;
}