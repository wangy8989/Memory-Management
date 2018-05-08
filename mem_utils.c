// CSE374 HW6
// Yicheng Wang & Yuhao Wang
// Implementation of function check_heap.

#include<stdio.h>
#include<inttypes.h>
#include<stdint.h>
#include<assert.h>
#include "mem_impl.h"
#include "mem.h"

// The chosen minimum block size
#define MIN_BLOCK_SIZE 16

extern freeNode* freeList;

// Check for possible problems with the free list data structure.
void check_heap() {
  freeNode *curr = freeList;
  freeNode *currnext = freeList;

  while (curr != NULL) {
  // block sizes are positive and not smaller than the chosen minimum block size
    assert(curr->size >= MIN_BLOCK_SIZE);
    currnext = curr->next;
    if (currnext != NULL) {
      // blocks are ordered with increasing memory addresses
      // blocks do not overlap and not touching
      assert((uintptr_t)curr + curr->size < (uintptr_t)currnext);
    }
    curr = curr->next;
  }
  // Function returns silently if no errors are detected.
}
