// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6
// Header file with declarations of internal implementation details shared by other 
// files within this project folder.

#ifndef MEM_IMPL_H
#define MEM_IMPL_H
#include <inttypes.h>

#define DEFAULT_BLOCK 8192
#define THRESHOLD 48
#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0xF)
#define HEADER_SIZE ALIGN(sizeof(Memblock)) 

void check_heap();

typedef struct mem_block {
    uintptr_t size;
    struct mem_block* next;  
} Memblock;

extern Memblock *head;
extern uintptr_t total_request;

Memblock* find_memblock(uintptr_t size);
void insert(Memblock *block);
void split_block(Memblock *block, uintptr_t size);
Memblock *merge_blocks(Memblock *block);
void remove_from_list(Memblock *block); 
#endif
