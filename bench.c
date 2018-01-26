// Bao Dinh & Daniel Merchant
// CSE 374 Au 17, Group AG
// 15 November 2017
// HW6

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mem.h"

int n_trials = N_TRIALS;
int pct_get = PCT_GET;
int pct_large = PCT_LARGE;
int small_limit = S_LIMIT;
int large_limit = L_LIMIT;
unsigned int random_seed = RAND_SEED;

int main(int argc, char** argv) {
    if (argc > 7) {
        fprintf(stderr, "too many arguments: bench"
        " requires 6 or fewer arguments\n");
        return EXIT_FAILURE;
    }
    initialize_args(argc - 1, &argv[1]);
    run_test();
    return 0;
}

// initialize the test arguments.
void initialize_args(int argc, char** args) {
  random_seed = (unsigned int) time(NULL);
    switch (argc) {
        case 1:
            n_trials = atoi(args[0]);
        case 2:
            pct_get = atoi(args[1]);
        case 3:
            pct_large = atoi(args[2]);
        case 4:
            small_limit = atoi(args[3]);
        case 5:
            large_limit = atoi(args[4]);
        case 6:
            random_seed = (unsigned int) atoi(args[5]);
    }
}

void run_test() {
    srand(random_seed);
    uintptr_t size;
    time_t start_time = clock();
    void **ptr_array = malloc(sizeof(void *) * n_trials);
    int ptr_array_size = 0;
    int ten_percent = n_trials / 10;
    uintptr_t total_size = 0;
    uintptr_t total_free = 0;
    uintptr_t n_free_blocks = 0;

    for (int i = 0; i < n_trials; i++) {
        int get_chance = rand() % 100;
        if (get_chance < pct_get) {
            int large_chance = rand() % 100;
            if (large_chance < pct_large) {
                size = (uintptr_t) rand() % (large_limit - small_limit) +
                small_limit;
            } else {
                size = (uintptr_t) rand() % small_limit + 1;
            }
            void *ptr = getmem(size);
            if (ptr != NULL) {
                //  store the value 0xFE in each of the first 16 bytes of
                //  the allocated block starting at the pointer address
                int bytes_init = (int) size > 16 ? 16 : (int) size;
                // converts to char since char size is 1 byte
                char init_value[16] = { 0xFE, 0xFE, 0xFE, 0xFE,
                    0xFE, 0xFE, 0xFE, 0xFE,
                    0xFE, 0xFE, 0xFE, 0xFE,
                    0xFE, 0xFE, 0xFE, 0xFE };
        memcpy(ptr, init_value, bytes_init);
        }
        ptr_array[ptr_array_size] = ptr;
            ptr_array_size++;
        } else {  // randomly removes previously allocated blocks to be freed.
            // calculates random value between 0 - (total ptr allocated - 1)
            if (ptr_array_size != 0) {  // remove Floating point exception
                int remove_index = rand() % ptr_array_size;
                freemem(ptr_array[remove_index]);
                // replace the removed index with the ptr at the last index
                ptr_array[remove_index] = ptr_array[ptr_array_size - 1];
                ptr_array_size--;
            }
        }
        // print statistics
        if ((i != 0) && (((i + 1) % ten_percent == 0))) {
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            print_statistics(start_time, total_size, total_free, n_free_blocks);
        }
    }
}

void print_statistics(time_t start_time, uintptr_t total_size,
    uintptr_t total_free, uintptr_t n_free_blocks) {
    time_t end_time = clock();
    double elapsed_time = (double) (end_time - start_time) / CLOCKS_PER_SEC;
    printf("Total CPU time used: %f\n", elapsed_time);
    printf("Total amount of storage acquired: %lu\n", total_size);
    printf("Total number of blocks on the free list: %lu\n", total_free);
    printf("Average number of bytes in the free list: %lu\n", n_free_blocks);
    printf("\n");
}
