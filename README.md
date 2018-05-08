# Memory-Management
Memory management project in C
Yicheng Wang & Yuhao Wang
3/2/2017

Yuhao Wang was responsible for getmem.c, .gitignore and Makefile. Yicheng Wang was responsible for freemem.c, mem.h, mem_utils.c, mem_impl.h, get_mem_stats.c, print_heap.c. Then, Yuhao Wang and Yicheng Wang worked on bench.c together. Later, we tested the program and fixed bugs together. At last, Yuhao Wang fixed all format issues and added comments using clint.py, and Yicheng Wang wrote README file.

Our free list is consist of free nodes. Each free node has a pointer size parameter and a link to next node. The free list is constructed in getmem.c given user's requested block size. Our default size of a block is 12000. If there is no such block in the current free list, get a new block. If there is such a block, we decide whether to divide the block and return to the user. The header size 16 is included in the size parameter, so current's node address plus the node's size is compared to the next node's address directly to make sure two nodes do not overlap. The smallest node size is 16 (just the header). They are both tested in check_heap function in mem_utils.c. 

In freemem.c, we return the block back to the free list. There are 3 big cases: the block belongs to the beginning of the list, in the middle of the list, and at the end of the list. In each case, we considered whether the block should merge to current node.

Result: when we use default values (ntrials=10000, pctget=50, pctlarge=10, small_limit=200, large_limit=20000), total cpu time used is 0.00179, total amount of storage required is 192528, total number of free block is 30 and average number of free bytes for each block is 3064.

when we take more trials given other parameters constant, it takes more cpu time. when we have greater probability of getmem instead of freemem and greater probability of getting a large block by the user, it intends to have more free blocks on the free list and more storage acquired. when we have larger limit of a large block requested by the user given others constant, the average number of free bytes on a free block is larger. when we set a random seed, the result will not change every time we make a test using the same parameters.

We googled on the header size and found out it is 16 when there is two parameters in the struct free node. We researched on clock function in bench.c to see how to record cpu time in a high precision of 6 digits. 

