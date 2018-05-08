// CSE374 HW6
// Yicheng Wang & Yuhao Wang
// Header file containing declarations of the public functions in the memory
// manager.

#include "mem_impl.h"

#ifndef mem_h
#define mem_h

void *getmem(uintptr_t size);
void freemem(void *p);
void get_mem_stats(uintptr_t *total_size, uintptr_t *total_free,
uintptr_t *n_free_blocks);
void print_heap(FILE *f);
void check_heap();
void getNewBlock(int size);

#endif
