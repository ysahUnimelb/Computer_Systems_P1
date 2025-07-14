#include <stdio.h>
#include "utils.h"

void task2(FILE *addressFile) {

    PageTableEntry pageTable[NUM_PAGES] = {0};  
    int freeFrameIndex = 0;

    unsigned int laddress;

    while (fscanf(addressFile, "%u", &laddress) == 1) {

        unsigned int maskedAddress = laddress & LOGICAL_ADDRESS_MASK;

        int pnumber = (maskedAddress >> 12) & PAGE_NUMBER_MASK;
        int offset = maskedAddress & OFFSET_MASK;

        printf("logical-address=%u,page-number=%d,offset=%d\n",
               laddress, pnumber, offset);

        int fnumber;
        int pfault = 0;

        if (!pageTable[pnumber].present) {
            pfault = 1;
            if (freeFrameIndex >= NUM_FRAMES) {
                fprintf(stderr, "Out of physical memory frames.\n");
                break;
            }
            fnumber = freeFrameIndex;
            pageTable[pnumber].present = 1;
            pageTable[pnumber].fnumber = fnumber;
            freeFrameIndex++;
        } else {
            fnumber = pageTable[pnumber].fnumber;
        }
        int paddress = fnumber * PAGE_SIZE + offset;

        printf("page-number=%d,page-fault=%d,frame-number=%d,physical-address=%d\n",
               pnumber, pfault, fnumber, paddress);
    }

}
