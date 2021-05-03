#include "utils.h"
#include "math.h"

ulong sieve1t(struct alg_options opt) {
	byte* tab;
	ulong i, j, cnt = 0;

	tab = (byte*)malloc(opt.max + 1);
	
	if (tab == NULL) {
		return -1;
	}
	
	memset(tab, 0, sizeof(byte) * (opt.max + 1));

	start_timer();

	for (i = 2; i <= opt.max; i++) {
		ulong max = (ulong)sqrt(opt.max);
	    if (tab[i]) {
	        continue;
	    }
		if (i >= opt.min) {
			cnt++; // found prime
			if (opt.verbose > 0) {
				log_prime(i);
			}
		}
		if (i <= max) {
			for (j = i; j <= opt.max; j += i) {
				tab[j] = 1;
			}
		}
	}

	stop_timer();

	free(tab);
	return cnt;
}