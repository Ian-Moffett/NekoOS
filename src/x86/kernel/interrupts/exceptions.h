#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "IDT.h"
#include "../drivers/VGA.h"


void div_0_ex(int_frame_t*);
void overflow_ex(int_frame_t*);
void bre_ex(int_frame_t*);
void invld_opcode_ex(int_frame_t*);
void dev_na_ex(int_frame_t*);
void double_fault_ex(int_frame_t*);
void cso_ex(int_frame_t*);
void invld_tss_ex(int_frame_t*);
void seg_np_ex(int_frame_t*);
void ss_fault_ex(int_frame_t*);
void gp_fault_ex(int_frame_t*);
void page_fault_ex(int_frame_t*);
void float_ex(int_frame_t*);


#endif
