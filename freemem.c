// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6
// This function is a simplified version of free which deallocates the memory previously
// allocated

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

void freemem(void *p) {
  // If p is NULL, then the call to freemem has no effect and returns immediately.
      if (p == NULL) {
        return;
      }
      check_heap();
      Memblock *bp = p - HEADER_SIZE;
      Memblock *prev = head;
      Memblock *curr = head;
      if ((uintptr_t) curr > (uintptr_t)bp) {
        bp->next = curr;
        head = bp;
      } else {
        curr = curr->next;
        while( curr && (uintptr_t)curr < (uintptr_t)bp) {
            prev = curr;
            curr = curr->next;
        }
        bp->next = curr;
        prev->next = bp;
      }
      bp = merge_blocks(bp);
      check_heap();
}
