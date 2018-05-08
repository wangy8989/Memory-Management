// CSE374 HW6
// Yicheng Wang & Yuhao Wang
// Implementation of function getmem.

#include<stdio.h>
#include<stdlib.h>
#include "mem_impl.h"
#include "mem.h"
#define DEFAULT_SIZE 12000  // default size

freeNode* freeList;
uintptr_t totalsize = 0;

// Return a pointer to a new block of storage with at least size bytes of memory
void* getmem(uintptr_t size) {
  check_heap();
  if (size <= 0) {
    return NULL;
  }
  // The actual size returned is a little bite larger than the required size
  int actual_size = (size/16 + 1) * 16;
  freeNode* current = freeList;
  freeNode* preNode;
  while (freeList != NULL && current->next != NULL &&
          current->size < actual_size) {
    current = current->next;
  }
  if (freeList == NULL || current->size < actual_size) {
    // if did not find an appropriate block for the user or the list is empty
    // then get a new block
    if (actual_size < DEFAULT_SIZE) {
      // required size is smaller than the default size
      getNewBlock(DEFAULT_SIZE);
    } else {  // required size is larger or equal to the default size
      getNewBlock(actual_size);
    }
  }
  // loop the list again to get the appropriate block for the user
  current = freeList;
  preNode = NULL;
  while (current->next != NULL && current->size < actual_size) {
    preNode = current;
    current = current->next;
  }
  // when current reaches the appropriate place, decide whether the block needs
  // to be divided or not
  if (preNode != NULL && current->size - actual_size <= 32) {
    // make sure the current node is not at the front node of the free list
    // when the block is large enough but not large enough to be divded
    preNode->next = current->next;
    current->next = NULL;
    check_heap();
    return (void*)((uintptr_t)current+16);
  } else if (preNode == NULL && current->size - actual_size <= 32) {
    // when the current node is at the front node of the free list
    // and the block is not large enough to be divided
    freeList = current->next;
    current->next = NULL;
    check_heap();
    return (void*)((uintptr_t)current+16);
  } else {  // when the block is large enough to be divided
    freeNode* newNode =
      (freeNode*)((uintptr_t)current + (current->size) - actual_size);
    newNode->size = actual_size;
    newNode->next = NULL;
    current->size = current->size - actual_size;
    check_heap();
    return (void*)((uintptr_t)newNode+16);
  }
}

// Get a new block of memory with the given size and sort the blocks in order
// of increasing address
void getNewBlock(int size) {
  freeNode* newNode = (freeNode*)malloc(size);
  newNode->size = size;
  totalsize += size;
  if (freeList == NULL) {
    freeList = newNode;
    newNode->next = NULL;
  } else {
    if ((uintptr_t)freeList > (uintptr_t)newNode) {
      newNode->next = freeList;
      freeList->next = NULL;
    } else {
      freeNode* temp = freeList;
      // go throught the list and sort the blocks in order of increasing address
      while (temp->next != NULL &&
            ((uintptr_t)(temp->next) < (uintptr_t)newNode)) {
        temp = temp->next;
      }
      if (temp->next == NULL) {  // when temp reaches the end of the list
        temp->next = newNode;
        newNode->next = NULL;
      } else {  // when temp reaches an appropriate place to insert the new node
        newNode->next = temp->next;
        temp->next = newNode;
      }
    }
  }
}
