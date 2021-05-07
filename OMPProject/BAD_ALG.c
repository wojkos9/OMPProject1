#include "utils.h"
#include <math.h>
#include <omp.h>

ulong naive_mt_dom(struct alg_options opt) {
	byte* tab;
	ulong* primes;
	ulong phase1_cnt = sqrt(opt.max);
	ulong i, j, cnt = 0, k = 0;

	tab = (byte*)malloc(opt.max + 1);
	primes = (ulong*)malloc((phase1_cnt + 1) * sizeof(*primes));

	if (tab == NULL || primes == NULL) {
		return -1;
	}

	memset(tab, 0, sizeof(byte) * (opt.max + 1));
	memset(primes, 0, (phase1_cnt + 1) * sizeof(*primes));

	omp_set_num_threads(opt.num_threads);

	start_timer();
	cnt = 0;
	tab[2] = 1;
	primes[k++] = 2;
	tab[3] = 1;
	primes[k++] = 3;
	for (i = 4; i <= phase1_cnt; i++) {
		ulong max = sqrt(i);
		tab[i] = 1;
		for (j = 2; j <= max; j++) {
			if (tab[j]) {
				if (i % j == 0) {
					tab[i] = 0;
					break;
				}
			}
			else continue;
		}
		if (tab[i]) {
			//cnt++;
			primes[k++] = i;
			if (opt.verbose > 0) {
				log_prime(i);
			}
		}
	}
	int tn = opt.num_threads;
	ulong leftmost = MAX(phase1_cnt + 1, opt.min);
	ulong n = opt.max - leftmost + 1;
	ulong width = ceil((double)n / tn);

#pragma omp parallel reduction(-:cnt)
	{
		int tid = omp_get_thread_num();

		ulong left = MIN(leftmost + tid * width, opt.max);
		ulong right = tid == tn - 1 ? opt.max : MIN(left + width - 1, opt.max);

		debug(2, "(%d) %llu..%llu\t\t%lld/%llu\n", tid, left, right, (right - left + 1), width);

		for (int i = left; i <= right; i++) {
			
			for (j = 0; j < k; j++) {
				tab[i] = 1;
				j = primes[j];
				if (tab[i]) {
					if (i % j == 0) {
						cnt--; // found composite in range
						tab[i] = 0;
						break;
					}
				}
			}
		}
	}



	stop_timer();

	free(tab);
	free(primes);
	return cnt;
}