/* Difei Lu
 * Cole Chamberlin
 * CSE 374, Hal Perkins
 * HW6, due: March 2, 2017
 *
 * frees the memory allocated at a pointer
 */

#include "mem.h"
#include "mem_impl.h"

void freemem(void *p) {
  check_heap();
  // return if it's null pointer
  if (p == NULL) {
    return;
  }

  // record the start address
  int addr = (uintptr_t)p;

  //
  free_node_t *curr = free_list;
  free_node_t *prev = NULL;

  //
  free_node_t *new = (free_node_t*)((uintptr_t)p);

  if (curr == NULL) {
    curr = new;
    curr->next = NULL;
  }

  while (curr != NULL) {
    //
    int prevaddr = (uintptr_t)prev;
    int curraddr = (uintptr_t)curr;

    if (prev == NULL) {
      // node belongs to the beginning of freelist
      // check if we need to merge the block
      if (addr + new->size == curraddr) {
        curr->size += new->size;
        new->next = NULL;
      } else {
        new->next = curr->next;
        curr = new;
      }
      return;
    } else if (addr > prevaddr && addr < curraddr) {
      // node belongs to middle of the freelist
      if (prevaddr + prev->size == addr && addr + new->size == curraddr) {
        // merge with both blocks before and after target block
        prev->size += new->size + curr->size;
        prev->next = curr->next;
        curr->next = NULL;
        curr = prev;
        new->next = NULL;
      } else if (prevaddr + prev->size == addr) {
        // merge with block before
        prev->size += new->size;
        new->next = NULL;
      } else if (addr + new->size == curraddr) {
        // merge with block after
        new->size += curr->size;
        new->next = curr->next;
        curr->next = NULL;
        prev->next = new;
        curr = prev;
      } else {
        // no merge needs to be done
        new->next = curr->next;
        curr->next = new;
      }
      return;
    } else if (curr->next == NULL) {
      // node belongs to the end of freelist
      // check if we need to merge the block
      if (addr == curraddr + curr->size) {
        curr->size += new->size;
      } else {
        curr->next = new;
      }
      new->next = NULL;
      return;
    }

    // advance pointer and record pervious one
    prev = curr;
    curr = curr->next;
  }
  check_heap();

}
