# CSE 374 HW6
# Yuhao Wang, Yicheng Wang
# Makefile for MemoryManagement program

# default target
bench: bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o
	gcc -Wall -g -std=c11 -o bench bench.o getmem.o freemem.o get_mem_stats.o print_heap.o mem_utils.o

# individual source files
getmem.o: getmem.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c getmem.c

freemem.o: freemem.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c freemem.c

get_mem_stats.o: get_mem_stats.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c get_mem_stats.c

print_heap.o: print_heap.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c print_heap.c

mem_utils.o: mem_utils.c mem_impl.h mem.h
	gcc -Wall -g -std=c11 -c mem_utils.c

#test program
test:
	./bench

test1:
	./bench 5000 80 50 500 3000 45

test2:
	./bench 100 50 50 100 15000

test3:
	./bench 999999

# "phony" target to remove built files and backups
clean:
	rm -f *.o bench
