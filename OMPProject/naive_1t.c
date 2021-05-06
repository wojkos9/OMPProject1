#include "utils.h"
#include <math.h>

ulong naive_1t(struct alg_options opt) {
	byte* tab;
	ulong* primes;
	ulong i, j, k = 0;
	ulong cnt = opt.max - opt.min + 1;
	ulong phase1_cnt = sqrt(opt.max);

	tab = (byte*)malloc(opt.max + 1);
	primes = (ulong*)malloc((phase1_cnt + 1) * sizeof(*primes));

	if (tab == NULL || primes == NULL) {
		return -1;
	}
	memset(tab, 1, sizeof(byte) * (opt.max + 1));

	start_timer();
	for (i = 2; i <= phase1_cnt; i++) {
		ulong max = sqrt(i);
		for (j = 2; j <= max; j++) {
			if (tab[j]) {
				debug(2, "%llu %llu\n", i, j);
				if (i % j == 0) {
					tab[i] = 0;
					debug(2, "not %llu\n", i);
					break;
				}
			}
			else continue;
		}
		if (tab[i]) {
			//cnt++;
			primes[k++] = i;
		}
	}
	for (i = opt.min; i <= opt.max; i++) {
		for (j = 0; j < k; j++) {
			if (sqrt(i) >= primes[j]) {
				debug(2, "%llu %llu\n", i, primes[j]);
				if (i % primes[j] == 0) {
				cnt--;
				debug(2, "not %llu\n", i);
				break;
				} 
			}
		}
	}
	stop_timer();

	if (opt.verbose) {
		for (i = opt.min; i <= opt.max; i++) {
			if (tab[i]) {
				log_prime(i);
			}
		}
	}

	free(tab);
	free(primes);
	return cnt;
}