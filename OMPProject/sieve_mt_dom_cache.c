#include "utils.h"
#include <omp.h>
#include <math.h>

#include "config.h"

ulong sieve_mt_dom_cache(struct alg_options opt) {
	byte* tab;
	ulong *primes;
	ulong phase1_cnt = sqrt(opt.max);
	ulong cnt = 0;
	ulong i, j, k = 0;

	cnt = opt.max - opt.min + 1;

	tab = (byte*)malloc(opt.max + 1);
	primes = (ulong *)malloc((phase1_cnt+1) * sizeof(*primes));

	if (tab == NULL || primes == NULL) {
		return -1;
	}
	memset(tab, 0, sizeof(byte) * (opt.max + 1));
	memset(primes, 0, (phase1_cnt + 1) * sizeof(*primes));

	omp_set_num_threads(opt.num_threads);
	
	
	ulong max = (ulong)sqrt(phase1_cnt);

	start_timer();

	// BEGIN compute first set
	for (i = 2; i <= phase1_cnt; i++) {
		if (tab[i]) {
			continue;
		}
		primes[k++] = i;
		if (i <= max) {
			for (j = 2 * i; j <= phase1_cnt; j += i) {
				if (!tab[j]) {
					if (j >= opt.min) {
						cnt--; // found composite
					}
					tab[j] = 1;
				}
			}
		}
	}
	// END compute first set

	int tn = opt.num_threads;
	ulong leftmost = MAX(phase1_cnt + 1, opt.min);
	ulong n = opt.max - leftmost + 1;
	ulong width = ceil((double)n / tn);
	int num_frags = ceil((double)n / CACHE_SIZE);

#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		ulong local_cnt = 0;
#pragma omp for
		for (int t = 0; t < num_frags; t++) {
			ulong left = MIN(leftmost + t * CACHE_SIZE, opt.max);
			ulong right = t == num_frags - 1 ? opt.max : MIN(left + CACHE_SIZE - 1, opt.max);

			debug(2, "(%d) %llu..%llu\t\t%lld/%llu\n", tid, left, right, (right - left + 1), CACHE_SIZE);

			for (int i = 0; i < k; i++) {
				ulong p = primes[i];
				ulong j = left + (p - left % p) % p;
				for (; j <= right; j += p) {
					if (!tab[j]) {
						local_cnt++; // found composite in range
						tab[j] = 1;
					}
				}
			}
		}
		
#pragma omp atomic
		cnt -= local_cnt;
	}

	stop_timer();

	if (opt.verbose) {
		for (i = opt.min; i <= opt.max; i++) {
			if (!tab[i]) {
				log_prime(i);
			}
		}
	}

	free(tab);
	free(primes);

	return cnt;
}