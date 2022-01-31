#ifndef PAGING_H
#define PAGING_H


typedef struct {
   unsigned int present : 1;   // Page present in memory.
   unsigned int rw : 1;   // Read-only if clear, readwrite if set.
   unsigned int user : 1;   // Supervisor level only if clear.
   unsigned int accessed : 1;   // Has the page been accessed since last refresh?
   unsigned int dirty : 1;   // Has the page been written to since last refresh?
   unsigned int unused : 7;   // Amalgamation of unused and reserved bits.
   unsigned int frame : 20;  // Frame address.
} page_t;


typedef struct {
    page_t pages[1024];
} page_tbl_t;


typedef struct {
    page_tbl_t* tables[1024];
    unsigned int tablesPhys[1024];
    unsigned int physAddr;      // Physical address of tablesPhys.
} page_dir_t;


void init_paging();


#endif
