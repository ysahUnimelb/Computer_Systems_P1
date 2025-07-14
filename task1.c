#include <stdio.h>
#include "utils.h"

void task1(FILE *addressFile) {

    unsigned int laddress = 0;
    unsigned int maskedAddress = 0;
    int pnumber = 0;
    int poffset = 0;

    // Reading addresses and parsing them
    while (fscanf(addressFile, "%u", &laddress) == 1) {
        maskedAddress = laddress & LOGICAL_ADDRESS_MASK;
        pnumber = (maskedAddress >> 12) & PAGE_NUMBER_MASK;
        poffset = maskedAddress & OFFSET_MASK;
        // Output
        printf("logical-address=%u,page-number=%d,offset=%d\n",
             laddress, pnumber, poffset);
    }
}
