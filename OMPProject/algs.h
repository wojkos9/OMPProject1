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
	makealg(naive_1t_2),			// 0
	makealg(sieve_1t),				// 1
	makealg(sieve_mt_dom),			// 2
	makealg(sieve_mt_fun),			// 3
	makealg(sieve_mt_dom_cache),	// 4
	makealg(naive_mt),				// 5
	//makealg(naive_mt_dom),			// 6
	
	
	
};