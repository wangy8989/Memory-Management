// CSE374 HW6
// Yuhao Wang, Yicheng Wang
// Function that get the current state of the memory manager

#include<stdio.h>
#include<stdint.h>
#include "mem.h"
#include "mem_impl.h"

extern uintptr_t totalsize;
extern freeNode* freeList;

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
    *total_size = totalsize;
    freeNode *curr = freeList;
    while (curr != NULL) {
        *total_free += curr->size;
        *n_free_blocks += 1;
        curr = curr->next;
    }
}
