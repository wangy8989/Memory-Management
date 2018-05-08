// CSE374 HW6
// Yicheng Wang & Yuhao Wang
// Header file with declarations of internal implementation details.

#include<stdint.h>

#ifndef mem_impl_h
#define mem_impl_h

// struct a free list node
struct freeNode {
  uintptr_t size;  // pointer size
  struct freeNode *next;  // next freenode
};

typedef struct freeNode freeNode;
void check_heap();

#endif

