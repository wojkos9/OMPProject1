#include "utils.h"
#include <math.h>
#include <omp.h>

ulong naive_mt(struct alg_options opt) {
	ulong i, j, k, cnt;

	ulong phase1_cnt = sqrt(opt.max);

	ulong* primes = malloc(sizeof(*primes) * phase1_cnt);

	start_timer();

	k = 0;
	cnt = 0;

	ulong left = MAX(opt.min, phase1_cnt + 1);

	for (i = 2; i <= phase1_cnt; i++) {
		byte is_prime = 1;
		ulong sqi = sqrt(i);
		for (j = 0; j < k && primes[j] <= sqi; j++) {
			if (i % primes[j] == 0) {
				is_prime = 0;
				break;
			}
		}
		if (is_prime) {
			if (i >= opt.min) cnt++;
			if (opt.verbose) log_prime(i);
			primes[k++] = i;
		}
	}
#pragma omp parallel for schedule(dynamic) reduction(+: cnt)
	for (ulong i = left; i <= opt.max; i++) {
		int tid = omp_get_thread_num();
		byte is_prime = 1;
		ulong sqi = sqrt(i);
		for (ulong j = 0; j < k && primes[j] <= sqi; j++) {
			if (i % primes[j] == 0) {
				is_prime = 0;
				break;
			}
		}
		if (is_prime) {
			if (opt.verbose) log_prime(i);
			cnt++;
		}
	}

	stop_timer();

	free(primes);
	return cnt;
}