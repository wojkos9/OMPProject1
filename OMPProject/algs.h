#pragma once
#include "utils.h"

#define makealg(name) {&name, #name}

extern algfun naive_1t;
extern algfun sieve_1t;
extern algfun sieve_mt_dom;

struct alg_t {
	algfun* fun;
	const char* name;
};

static struct alg_t ALGS_LIST[] = {
	makealg(naive_1t),
	makealg(sieve_1t),
	makealg(sieve_mt_dom),
};