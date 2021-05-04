#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#include "getopt.h"
#include "utils.h"
#include "algs.h"

#define MAXPRIME ((ulong) 1e8 )

static const char *help_str = ""
"0\tsingle-threaded naive\n"
"1\tsingle-threaded sieve\n";

int main(int argc, char* argv[]) { 
    int c;

    struct alg_options opt = {
        .min = 2, 
        .max = MAXPRIME, 
        .verbose = 0, 
        .num_threads = 4};

    algfun *algs[] = {&naive1t, &sieve1t};
    int alg_cmp[] = { 1, 1 };
    algfun* fun;

    DEBUG_LVL = 1;

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
                        debug("Invalid number of threads; %s\n", optarg);
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
        algfun *fun = algs[algn];

        debug(0, "\nStarting alg %d (MIN=%llu, MAX=%llu)\n", algn, opt.min, opt.max);

        ulong nprimes = fun(opt);

        debug(1, "\nPrimes count: %llu\n", nprimes);
        debug(0, "Execution time: %lf s\n", read_timer());
    }
    

    return 0;
}