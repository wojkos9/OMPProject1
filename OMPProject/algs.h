#pragma once
#include "utils.h"

#define makealg(name) {&name, #name}

extern algfun naive_1t;
extern algfun sieve_1t;
extern algfun sieve_mt_dom;
extern algfun sieve_mt_fun;
extern algfun sieve_mt_dom_cache;
extern algfun naive_mt_dom;
extern algfun naive_1t_2;
extern algfun naive_mt;

struct alg_t {
	algfun* fun;
	const char* name;
};

static struct alg_t ALGS_LIST[] = {
	makealg(naive_1t),
	makealg(sieve_1t),
	makealg(sieve_mt_dom),
	makealg(sieve_mt_fun),
	makealg(sieve_mt_dom_cache),
	makealg(naive_mt_dom),
	makealg(naive_1t_2),
	makealg(naive_mt),
	
	
};