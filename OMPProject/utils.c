#include "utils.h"


void log_prime(ulong prime) {
	static int print_cnt;
    if (!prime) { // reset offset
        print_cnt = 0;
        return;
    }
	debug(0, "%llu%c", prime, print_cnt < 9 ? '\t' : '\n');
	print_cnt = (print_cnt + 1) % 10;
}

#include <Windows.h>
static LARGE_INTEGER _alg_timer_start;
static LARGE_INTEGER _alg_timer_end;

int DEBUG_LVL = 0;

void start_timer() {
    debug(3, "\nStart timer\n");
    QueryPerformanceCounter(&_alg_timer_start);
}

void stop_timer() {
    debug(3, "\nStop timer\n");
    QueryPerformanceCounter(&_alg_timer_end);
}

double read_timer() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return (double)(_alg_timer_end.QuadPart - _alg_timer_start.QuadPart) / frequency.QuadPart;
}
