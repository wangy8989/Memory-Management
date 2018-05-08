// CSE374 HW6
// Yuhao Wang, Yicheng Wang
// Function that frees the allocated memory

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "mem.h"
#include "mem_impl.h"

extern freeNode* freeList;

// The method takes in a pointer that points to the block to be freed
// The block is inserted into the free list
void freemem(void* p) {
  check_heap();

  // If p is NULL, the call to freemem has no effect and returns immediately.
  if (p == NULL) {
    return;
  }

  // address of the node
  freeNode* newNode = (freeNode*)((uintptr_t)p - 16);

  // if the free list is now empty
  if (freeList == NULL) {
    freeList = newNode;
    freeList->next = NULL;
  } else {
    freeNode* current = freeList;
    // add the node to the beginning of the free list
    if ((uintptr_t)newNode < (uintptr_t)current) {
      if ((uintptr_t)newNode + newNode->size == (uintptr_t)current) {
        // merge to the first node
        newNode->size += current->size;
        newNode->next = current->next;
        freeList = newNode;
        check_heap();
        return;
      } else {
        freeList = newNode;
        newNode->next = current;
        check_heap();
        return;
      }
    }

    while (current != NULL) {
      // if reached the end of free list
      if (current->next == NULL) {
        if ((uintptr_t)current + current->size == (uintptr_t)newNode) {
          // merge to the last node
          current->size += newNode->size;
          check_heap();
          return;
        } else {
          // add the node to the end of the free list
          current->next = newNode;
          newNode->next = NULL;
          check_heap();
          return;
        }
      } else {
        if ((uintptr_t)newNode < (uintptr_t)current->next) {
          newNode->next = current->next;
          current->next = newNode;
          if ((uintptr_t)current+current->size == (uintptr_t)newNode) {
            current->size += newNode->size;
            current->next = current->next->next;
            if ((uintptr_t)current+current->size == (uintptr_t)current->next) {
              current->size += current->next->size;
              current->next = current->next->next;
          }
            check_heap();
            return;
          } else if ((uintptr_t)newNode + newNode->size ==
                    (uintptr_t)newNode->next) {
            newNode->size += newNode->next->size;
            newNode->next = newNode->next->next;
            check_heap();
            return;
          }
          check_heap();
          return;
        }
      }
      current = current->next;
    }
  }
}
