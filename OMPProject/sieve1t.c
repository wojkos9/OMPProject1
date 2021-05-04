#include "utils.h"
#include "math.h"

ulong sieve1t(struct alg_options opt) {
	byte* tab;
	ulong i, j, cnt;
	ulong last_prime = 0;

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

		if (opt.verbose && i >= opt.min) {
			last_prime = i;
			log_prime(i);
		}

		for (j = 2 * i; j <= opt.max; j += i) {
			if (!tab[j]) {
				if (j >= opt.min) {
					cnt--; // found composite
				}
				
				tab[j] = 1;
			}
		}
	}

	stop_timer();

	if (opt.verbose) {
		for (i = MAX(last_prime + 1, opt.min); i <= opt.max; i++) {
			if (!tab[i]) log_prime(i);
		}
	}

	free(tab);
	return cnt;
}