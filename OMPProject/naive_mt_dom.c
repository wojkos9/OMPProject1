#include "utils.h"
#include <math.h>
#include <omp.h>

ulong naive_mt_dom(struct alg_options opt) {
	byte* tab;
	ulong* primes;
	ulong phase1_cnt = sqrt(opt.max);
	ulong i, j, cnt = 0;

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
	tab[3] = 1;
	for (i = 4; i <= opt.max; i++) {
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
			cnt++;
			if (opt.verbose > 0) {
				log_prime(i);
			}
		}
	}
	int tn = opt.num_threads;
	ulong leftmost = MAX(phase1_cnt + 1, opt.min);
	ulong n = opt.max - leftmost + 1;
	ulong width = ceil((double)n / tn);

	stop_timer();

	free(tab);
	return cnt + 2;
}