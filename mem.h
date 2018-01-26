// Bao Dinh & Daniel Merchant
// CSE 374
// Assignment 6

// Header file that declares the public functions in our memory manager
#include <stdio.h>
#include <inttypes.h>
#include "mem_impl.h"
#ifndef MEM_H
#define MEM_H

// Default values for bench
#define N_TRIALS 10000
#define PCT_GET 50 
#define PCT_LARGE 10
#define S_LIMIT 200
#define L_LIMIT 20000
#define RAND_SEED 0 

void initialize_args();

void* getmem(uintptr_t size);

void freemem(void* p);

void get_mem_stats(uintptr_t* total_size, 
uintptr_t* total_free, uintptr_t* n_free_blocks);

void run_test();

void print_heap(FILE* f);

#endif
