# C Memory Management Package 


## Overview
This repository contains code for a group project in my CSE 374 course at the University of Washington. My partner was Daniel Merchant. We had to implement a memory management package that has the same basic functionalitity as the standard library malloc and free functions. 

## Technical Description

At the core, the getmem and freemem functions share a single data structure, the free list, which is just a linked-list of free memory blocks that are available to satisfy memory allocation requests. For getmem, we used a util function to find and return the pointer of a certain memory block given the size. This allowed us to determine whether we had to request more memory from the underlying system. Given that we have memory block of sufficient size on our free list, split the block accordingly given that memory block and size requested. 

Our freemem acts accordingly by checking the address size of the memory block prior to inserting it back into the freelist. We utilize an util function that merges blocks of memory if they're adjacent in their physical memory address. 

