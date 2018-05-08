// CSE374 HW6
// Yicheng Wang & Yuhao Wang
// Implementation of function print_heap.

#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include "mem_impl.h"
#include "mem.h"

extern freeNode* freeList;

// Print a formatted listing on file f showing the the blocks on the free list.
void print_heap(FILE *f) {
  freeNode *curr = freeList;
  while (curr != NULL) {
    fprintf(f, "%p 0x%" PRIxPTR "\n", curr, (uintptr_t)(curr->size));
    curr = curr->next;
  }
}
