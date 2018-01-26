// Bao Dinh & Daniel Merchant 
// CSE 374
// Assignment 6
// Utility functions that can be used throughout our other files

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "mem_impl.h"
#include "mem.h"

Memblock *head = NULL;
uintptr_t total_request = 0;

// Checks the structure of the heap for errors.
// The heap must be ordered with strictly increasing memory indices.
// Each block in the heap must have size greater than the minimum threshold.
// Each block address must not be in the middle of memory controlled by 
// another block.
void check_heap() {
    Memblock *current = head;
    while (current) {
        // make sure size is positive and greater than the threshold
        assert(current->size >= THRESHOLD);
        if (current->next) {
            // check that mem addresses are in increasing order,
            // and that they aren't touching each other
            assert((uintptr_t)current < (uintptr_t)current->next);
        }
        Memblock *addr_check = head;
        while (addr_check && addr_check->next) {
            assert((uintptr_t)current > (uintptr_t)addr_check 
                && (uintptr_t)current < (uintptr_t)addr_check->next);
            addr_check = addr_check->next;
        }
        current = current->next; 
    }
}

// Find the first block in the last that satisfies the request.
// Todo: Fix case where head is returned and isn't the right block for the request
Memblock* find_memblock(uintptr_t size) {
    Memblock *bp = head;
    while (bp && bp->size < size) {
        bp = bp->next;
    }
    return bp;
}

// remove the memblock from the free list.
void remove_from_list(Memblock *block) {
    if (block == head) {
        if (!head->next) { // If head is the only block on the list
            head = NULL;
        }
        else {
            head = head->next;
            block->next = NULL;
        }
        return;
    }
    
    Memblock *prev = head; 
    while (prev-> next != block) {  // find block before the block we want to remove
        prev = prev->next;
    }
    prev->next = block->next;
    block->next = NULL;    
}

// Split block into two blocks.
void split_block(Memblock *block, uintptr_t size) {    
    Memblock *bp =(Memblock*)((uintptr_t)block + HEADER_SIZE + size);
    bp->size = (block->size - size - HEADER_SIZE);
    bp->next = block->next;
    block->size = size;
    block->next = bp;
}

// Insert a freed block back into the list
void insert(Memblock *block) {
    if (!head) {
        head = block;
        return;
    }
    Memblock *bp = head;
    while (bp->next && (uintptr_t)bp->next < (uintptr_t)block) {
        bp = bp->next;
    }
    block->next = bp->next;
    bp->next = block;
    bp = merge_blocks(bp);
}

// Merge blocks back together when adding blocks
// back to the free list. Only do this if the blocks
// are adjacent to each other in memory. Return pointer 
// to the block from which you started.
Memblock *merge_blocks(Memblock *block) {
    while ((uintptr_t)block->next == (uintptr_t)block + block->size + HEADER_SIZE) {
        block->size += (HEADER_SIZE + block->next->size);
        block->next = block->next->next;
    }
    return block;
}

