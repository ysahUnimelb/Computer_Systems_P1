#include <stdio.h>
#include "utils.h"

void task4(FILE *addressFile) {

    PageTableEntry pageTable[NUM_PAGES] = {0};
    int frameToPage[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) frameToPage[i] = -1;

    int frameQ[NUM_FRAMES];
    int front = 0, size = 0;

    TLBEntry tlb[TLB_SIZE];
    for (int i = 0; i < TLB_SIZE; i++) tlb[i].valid = 0;
    int time = 0;
    unsigned int laddress;
    while (fscanf(addressFile, "%u", &laddress) == 1) {
        time++;
        
        unsigned int maskedAddress = laddress & LOGICAL_ADDRESS_MASK;
        int pageNumber = (maskedAddress >> 12) & PAGE_NUMBER_MASK;
        int offset = maskedAddress & OFFSET_MASK;

        printf("logical-address=%u,page-number=%d,offset=%d\n",
               laddress, pageNumber, offset);

        int tlbHit = 0;
        int fnumber = -1;

        // Checking TLB
        for (int i = 0; i < TLB_SIZE; i++) {
            if (tlb[i].valid && tlb[i].pageNumber == pageNumber) {
                tlbHit = 1;
                fnumber = tlb[i].frameNumber;
                tlb[i].lastUsed = time;
                break;
            }
        }
        if (tlbHit) {
            printf("tlb-hit=1,page-number=%d,frame=%d,physical-address=%d\n",
                   pageNumber, fnumber, fnumber * PAGE_SIZE + offset);
            continue;
        }
        printf("tlb-hit=0,page-number=%d,frame=none,physical-address=none\n", pageNumber);

        int pageFault = 0;

        if (!pageTable[pageNumber].present) {
            pageFault = 1;

            if (size < NUM_FRAMES) {
                fnumber = size;
                size++;
            } else {
                int fframe = frameQ[front];
                int epage = frameToPage[fframe];

                printf("evicted-page=%d,freed-frame=%d\n", epage, fframe);
                pageTable[epage].present = 0;
                int flushed = 0; //variable for tlb flush
                for (int i = 0; i < TLB_SIZE; i++) {
                    if (tlb[i].valid && tlb[i].pageNumber == epage) {
                        tlb[i].valid = 0;
                        flushed = 1;
                        break;
                    }
                }
                if (flushed) {
                    int count = 0;
                    for (int i = 0; i < TLB_SIZE; i++) {
                        if (tlb[i].valid) count++;
                    }
                    printf("tlb-flush=%d,tlb-size=%d\n", epage, count);
                }

                fnumber = fframe;
                front = (front + 1) % NUM_FRAMES;
            }

            pageTable[pageNumber].present = 1;
            pageTable[pageNumber].fnumber = fnumber;
            frameToPage[fnumber] = pageNumber;
        } else {
            fnumber = pageTable[pageNumber].fnumber;
        }
        // Added new TLB entry
        int index = -1;
        for (int i = 0; i < TLB_SIZE; i++) {
            if (!tlb[i].valid) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            int time_lru = __INT_MAX__;
            for (int i = 0; i < TLB_SIZE; i++) {
                if (tlb[i].lastUsed < time_lru) {
                    time_lru = tlb[i].lastUsed;
                    index = i;
                }
            }
            printf("tlb-remove=%d,", tlb[index].pageNumber);
        } else {
            printf("tlb-remove=none,");
        }
        tlb[index].pageNumber = pageNumber;
        tlb[index].frameNumber = fnumber;
        tlb[index].valid = 1;
        tlb[index].lastUsed = time;
        printf("tlb-add=%d\n", pageNumber);

        int paddress = fnumber * PAGE_SIZE + offset;
        printf("page-number=%d,page-fault=%d,frame-number=%d,physical-address=%d\n",
               pageNumber, pageFault, fnumber, paddress);
    }
}
