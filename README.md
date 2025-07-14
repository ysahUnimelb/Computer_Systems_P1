In this project, you will write a program that simulates a virtual memory manager. The memory
manager will rely on the use of a TLB and a page table to translate logical addresses to physical
addresses and will manage the allocation of logical pages to physical frames. For simplicity and
to avoid implementing any logic related to process management (e.g., process scheduling), you
will assume memory management is done for a single process that runs for the duration of the
simulation.
The input to your program will be an ordered sequence of memory accesses (see Section 7). For
simplicity, all memory accesses are assumed to be read operations (i.e., your program does not
need to manage memory accesses that update/write data). For each memory access, the memory
manager will extract the page number and the offset from the logical address (see Section 3) and
translate it into a physical address by using the TLB and/or page table (see Sections 4 and 6). In
cases in which a page is being accessed but physical memory is full (i.e., all frames are allocated),
your program will rely on a FIFO page replacement algorithm to decide which page to evict in
order to load the new page into memory (
