#include "utils.h"
#include <omp.h>
#include <math.h>
#include "config.h"

ulong sieve_mt_fun(struct alg_options opt) {
	byte* tab;
	ulong *primes;
	ulong phase1_cnt = sqrt(opt.max);
	ulong cnt = 0;
	ulong i, j, k = 0;

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
					tab[j] = 1;
				}
			}
		}
	}
	// END compute first set

	int tn = opt.num_threads;
	ulong leftmost = MAX(phase1_cnt + 1, opt.min);
	ulong left = leftmost;
	ulong right = opt.max;

#pragma omp parallel
	{
		int tid = omp_get_thread_num();

		for (int i = tid; i < k; i += tn) {
			ulong p = primes[i];
			ulong j = left + (p - left % p) % p;
			for (; j <= right; j += p) {
				if (!tab[j]) {
					tab[j] = 1;
				}
			}
		}

#pragma omp barrier

#ifdef COUNT
#pragma omp for reduction(+:cnt)
		for (j = opt.min; j <= opt.max; j++) {
			if (!tab[j]) {
				cnt++;
			}
		}
#endif
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