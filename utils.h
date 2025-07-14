#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>
#include <stdio.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 1024
#define NUM_FRAMES 256
#define OFFSET_MASK 0xFFF
#define PAGE_NUMBER_MASK 0x3FF
#define LOGICAL_ADDRESS_MASK 0x3FFFFF
#define TLB_SIZE 32

typedef struct {
    int present;
    int fnumber;
} PageTableEntry;

typedef struct {
    int pageNumber;
    int frameNumber;
    int valid;
    int lastUsed; // for LRU
} TLBEntry;

void task1(FILE *addressFile);
void task2(FILE *addressFile);
void task3(FILE *addressFile);
void task4(FILE *addressFile);

#endif