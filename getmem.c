// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6
// This function acts as a simplified version of Malloc and allocates requested
// memory and returns a pointer to it. 

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem_impl.h"
#include "mem.h"

// Search the free list for a memory block with enough memory to
// satisfy the request. If no satisfactory block is found, request
// more memory from the underlying system and allocate it.
void* getmem(uintptr_t size) {
    if (size < 1) {
        return NULL;
    }
    check_heap();
    uintptr_t newsize;
    newsize = ALIGN(size);
    Memblock *bp = find_memblock(newsize);

    if (!bp && size < DEFAULT_BLOCK) {
        newsize = DEFAULT_BLOCK;
     } else if (size < THRESHOLD) { // Prevents tiny blocks of memory from being allocated
        newsize = THRESHOLD;
    }

    if (!bp || bp->size < newsize) {  // If a block couldn't be found
        bp = (Memblock *)malloc(HEADER_SIZE+newsize); // build a new block
        bp->size = newsize; 
        total_request += newsize;  // keep track of the total memory allocated
        insert(bp); 
    }
    if (bp->size >= (size + HEADER_SIZE + THRESHOLD)) { 
        split_block(bp, ALIGN(size));
    }
    remove_from_list(bp);
    
    uintptr_t mem_addr = (uintptr_t)bp + HEADER_SIZE;
    check_heap();
    return (void*)mem_addr;
}
