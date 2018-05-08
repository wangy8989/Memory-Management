/* Difei Lu
 * Cole Chamberlin
 * CSE 374, Hal Perkins
 * HW6, due: March 2, 2017
 *
 * program to benchmark performance of memory allocator
 */

#define _POSIX_C_SOURCE 199309L

#include "mem.h"
#include "mem_impl.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    int random_seed = time(NULL);
    
    for (int i = 1; i < argc; i++) {
        switch(i) {
            case 1:
                ntrials = *argv[i];
                break;
            case 2:
                pctget = *argv[i];
                break;
            case 3:
                pctlarge = *argv[i];
                break;
            case 4:
                small_limit = *argv[i];
                break;
            case 5:
                large_limit = *argv[i];
                break;
            case 6:
                random_seed = *argv[i];
                break;
        }
    }

    srand(random_seed);
    int total = 0;
    uintptr_t *mem_list = malloc(ntrials * sizeof(uintptr_t));
    int i = 0;
    // create variables to store results of get_mem_stats
    uintptr_t total_size;
    uintptr_t total_free;
    uintptr_t n_free_blocks;
    // get starting time
    struct timespec *start = (struct timespec *)malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_REALTIME, start);
    long s = 1000000000 * start->tv_sec + start->tv_nsec;
    for (int j = 0; j < ntrials; j++) {
        int pct = rand() % 100;
        // print information 10 times throughout trial
        if (j != 0 && j % (ntrials / 10) == 0) {
            struct timespec *curr = (struct timespec *)malloc(sizeof(struct timespec));
            clock_gettime(CLOCK_REALTIME, curr);
            long c = 1000000000 * curr->tv_sec + curr->tv_nsec;
            printf("time: %f", (double)(c - s)/(double)1000000000);
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            printf(" total alloc: %d, total free: %d, average size: %d\n", (int)total_size, (int)total_free, 
                    n_free_blocks ? (int)total_free / (int)n_free_blocks : 0);

        }
        if (pct < pctget) {
            int size;
            pct = rand() % 100;
            if (pct < pctlarge)
                size = small_limit + rand() % (large_limit - small_limit);
            else
                size = rand() % small_limit;
            mem_list[i] = (uintptr_t)getmem(size);
            total += size;
            i++;
        } else if (i > 0) {
            // get random position and remove memory
            int pos = rand() % i;
            freemem((void *)mem_list[pos]);
            mem_list[pos] = mem_list[i];
            i--;
        }
        
    }
    // get ending time
    struct timespec *end = (struct timespec *)malloc(sizeof(struct timespec *));
    clock_gettime(CLOCK_REALTIME, end);
    long e = 1000000000 * end->tv_sec + end->tv_nsec;
    // print total time
    printf("time: %f", (double)(e - s)/(double)1000000000);
    get_mem_stats(&total_size, &total_free, &n_free_blocks);
    printf(" total alloc: %d, total free: %d, average size: %d\n", (int)total_size, (int)total_free, 
                    n_free_blocks ? (int)total_free / (int)n_free_blocks : 0);
    print_heap(stdin);
    return 1;
}
