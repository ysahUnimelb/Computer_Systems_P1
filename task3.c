#include <stdio.h>
#include "utils.h"

void task3(FILE *addressFile) {

    PageTableEntry pageTable[NUM_PAGES] = {0};
    int frameToPage[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) frameToPage[i] = -1;

    int pageQueue[NUM_FRAMES];  // FIFO queue of page numbers
    int front = 0, rear = 0, frameCount = 0;

    unsigned int logicalAddress;
    while (fscanf(addressFile, "%u", &logicalAddress) == 1) {
        unsigned int maskedAddress = logicalAddress & LOGICAL_ADDRESS_MASK;
        int pageNumber = (maskedAddress >> 12) & PAGE_NUMBER_MASK;
        int offset = maskedAddress & OFFSET_MASK;

        printf("logical-address=%u,page-number=%d,offset=%d\n",
               logicalAddress, pageNumber, offset);
               int fnumber;
               int pageFault = 0;
               if (!pageTable[pageNumber].present) {
                   pageFault = 1;
                   if (frameCount < NUM_FRAMES) {
                       fnumber = frameCount;
                       frameCount++;
                   } else {
                       //evict
                       int fframe = pageQueue[front];
                       int epage = frameToPage[fframe];

                printf("evicted-page=%d,freed-frame=%d\n", epage, fframe);
                pageTable[epage].present = 0;
                fnumber = fframe;
                front = (front + 1) % NUM_FRAMES;
            }
            // Loading the page into the frame
            pageTable[pageNumber].present = 1;
            pageTable[pageNumber].fnumber = fnumber;
            frameToPage[fnumber] = pageNumber;
            pageQueue[rear] = fnumber;
            rear = (rear + 1) % NUM_FRAMES;
        } else {
            fnumber = pageTable[pageNumber].fnumber;
        }
        int physicalAddress = fnumber * PAGE_SIZE + offset;
        printf("page-number=%d,page-fault=%d,frame-number=%d,physical-address=%d\n",
               pageNumber, pageFault, fnumber, physicalAddress);
    }

}
              