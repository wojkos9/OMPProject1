#include "utils.h"


void log_prime(ulong prime) {
	static int print_cnt;
	debug("%llu%c", prime, print_cnt < 9 ? '\t' : '\n');
	print_cnt = (print_cnt + 1) % 10;
}

#include <Windows.h>
static LARGE_INTEGER _alg_timer_start;
static LARGE_INTEGER _alg_timer_end;

void start_timer() {
    debug("\nStart timer\n");
    QueryPerformanceCounter(&_alg_timer_start);
}

void stop_timer() {
    debug("\nStop timer\n");
    QueryPerformanceCounter(&_alg_timer_end);
}

double read_timer() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return (double)(_alg_timer_end.QuadPart - _alg_timer_start.QuadPart) / frequency.QuadPart;
}