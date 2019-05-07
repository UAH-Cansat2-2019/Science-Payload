/*
 * RingBuff.h
 *
 * Created: 5/4/2019 10:59:50 PM
 *  Author: natha
 */ 


#ifndef RINGBUFF_H_
#define RINGBUFF_H_

#define BUFSIZE 10

struct uint16RingBuff {
	uint16_t * data;
	uint8_t  lastItem;
	};
typedef struct uint16RingBuff* p_bstru;
void u16BuffInit(p_bstru rstru);
void putu16(p_bstru d_struct,uint16_t data);
uint16_t getu16(p_bstru d_struct,int16_t index);
void array_recent(p_bstru bufStru,uint16_t * fRec,uint8_t N);

#endif /* RINGBUFF_H_ */