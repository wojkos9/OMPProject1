#include "utils.h"
#include "math.h"

ulong sieve_1t(struct alg_options opt) {
	byte* tab;
	ulong i, j, cnt;

	cnt = opt.max - opt.min + 1;

	tab = (byte*)malloc(opt.max + 1);

	if (tab == NULL) {
		return -1;
	}

	memset(tab, 0, sizeof(byte) * (opt.max + 1));

	start_timer();

	ulong max = (ulong)sqrt(opt.max);
	for (i = 2; i <= max; i++) {
		if (tab[i]) {
			continue;
		}
		
		for (j = 2 * i; j <= max; j += i) {
			if (!tab[j]) {
				tab[j] = 1;
				if (j >= opt.min) {
					cnt--;
				}
			}
		}
		for (j = opt.min + (i - opt.min % i) % i; j <= opt.max; j += i) {
			if (!tab[j]) {
				cnt--; // found composite
				tab[j] = 1;
			}
		}
	}

	stop_timer();

	if (opt.verbose) {
		for (i = opt.min; i <= opt.max; i++) {
			if (!tab[i]) log_prime(i);
		}
	}

	free(tab);
	return cnt;
}