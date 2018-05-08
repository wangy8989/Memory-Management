// CSE374 HW6
// Yuhao Wang, Yicheng Wang
// Main part of the program
// This program should execute a large number of calls to functions getmem and
// freemem to allocate and free blocks of random sizes and in random order.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include "mem.h"

int main(int argc, char** argv) {
  // Default values if not given by the user:
  // total number of getmem plus freemem calls to randomly perform during this
  // test.
  int ntrials = 10000;
  // percent of the total getmem/freemem calls that should be getmem.
  int pctget = 50;
  // percent of the getmem calls that should request "large" blocks with a size
  // greater than small_limit.
  int pctlarge = 10;
  // largest size in bytes of a "small" block.
  int small_limit = 200;
  // largest size in bytes of a "large" block.
  int large_limit = 20000;
  // initial seed value for the random number generator.
  // using the system time-of-day clock.
  unsigned int random_seed = (unsigned int)time(NULL);

  // if values are given by the user, use that value instead of default values
  if (argc > 1) {
    ntrials = atoi(argv[1]);   // convert characters into integers
  }
  if (argc > 2) {
    pctget = atoi(argv[2]);
  }
  if (argc > 3) {
    pctlarge = atoi(argv[3]);
  }
  if (argc > 4) {
    small_limit = atoi(argv[4]);
  }
  if (argc > 5) {
    large_limit = atoi(argv[5]);
  }
  if (argc > 6) {
    random_seed = atoi(argv[6]);
  }

  // initialize variables
  int getmem_number = ntrials * pctget / 100;
  void *memory_arr[getmem_number];
  int arr_index = 0;
  int size;
  int rand_free;
  struct timeval start_time, end_time;
  gettimeofday(&start_time, NULL);
  double cpu;
  srand(random_seed);

  // simulate n trials
  for (int i = 1; i <= ntrials; i++) {
    // simulate getmem
    if ((rand() % 100 < pctget) && (arr_index < getmem_number)) {
      // simulate getting large blocks
      if (rand() % 100 < pctlarge) {
        size = small_limit + rand() % (large_limit - small_limit);
      } else {
        // simulate getting small blocks
        size = rand() % small_limit + 1;
      }
      memory_arr[arr_index] = getmem(size);
      arr_index++;

      // simulate freemem
    } else {
      // if the array is not empty, randomly free a block
      if (arr_index != 0) {
        // pick a random number between 0 and (arr_end-1)
        rand_free = rand() % arr_index;
        freemem(memory_arr[rand_free]);
        memory_arr[rand_free] = memory_arr[arr_index - 1];
        memory_arr[arr_index - 1] = NULL;
        arr_index--;
      }
    }

    // print the result 10 times evenly during execution
    if (i % (ntrials / 10) == 0) {
      uintptr_t total_size = 0;
      uintptr_t total_free = 0;
      uintptr_t n_free_blocks = 0;
      // get cpu time
      gettimeofday(&end_time, NULL);
      cpu = (end_time.tv_usec - start_time.tv_usec) / 1000000.0f;
      // get stats for free list
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      double average_block;
      if (n_free_blocks == 0) {  // if the denominator is 0, the result is 0.
        average_block = 0;
      } else {
        average_block = (double)total_free / (double)n_free_blocks;
      }
      printf("(%d%%) ", 10 * i / (ntrials / 10));
      printf("total CPU time: %.5f, ", cpu);
      printf("total amount of storage acquired: %lu, ", total_size);
      printf("total number of free blocks: %lu, ", n_free_blocks);
      printf("average number of free bytes: %.2f\n", average_block);
    }
  }
  return 0;
}
