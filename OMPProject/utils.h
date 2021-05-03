#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned long long ulong;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define arrlen(x) (sizeof(x)/sizeof(x[0]))

struct alg_options {
	ulong min;
	ulong max;
	int verbose;
};

struct exec_result {
	ulong nprimes;
	double time;
};

typedef ulong(algfun)(struct alg_options);

extern void log_prime(ulong prime);

extern void start_timer();
extern void stop_timer();
extern double read_timer();