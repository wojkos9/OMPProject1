#include "utils.h"
#include <math.h>

ulong naive_1t(struct alg_options opt) {
	byte* tab;
	ulong i, j, cnt = 0;

	tab = (byte*)malloc(opt.max + 1);

	if (tab == NULL) {
		return -1;
	}

	memset(tab, 0, sizeof(byte) * (opt.max + 1));

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
	stop_timer();

	free(tab);
	return cnt+2;
}