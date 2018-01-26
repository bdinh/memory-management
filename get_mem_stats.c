// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6
// Stores statistics about the current state of the memory manager

#include <stdio.h>
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

// Updates the value of the pointers accordingly based on the current free list
void get_mem_stats(uintptr_t *total_size, uintptr_t *total_free, uintptr_t *n_free_blocks) {
    *total_size = total_request;
    Memblock *bp = head;

    while (bp != NULL) {
      *total_free += bp->size;
      *n_free_blocks += (uintptr_t) 1;
      bp = bp->next;
    }
}
