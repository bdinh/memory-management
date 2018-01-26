// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6
// Prints a formatted listing on file f showing the blocks on the free list

#include <stdio.h>
#include "mem_impl.h"
#include "mem.h"

// Prints the content of the heap. Primarily used for testing purposes.
void print_heap(FILE *f) {
  if(f) {
    Memblock *bp = head;
    while (bp) {
      fprintf(f, "Address: %p Length: %p \n", bp, (Memblock *) bp->size);
      bp = bp->next;
    }

  }
}
