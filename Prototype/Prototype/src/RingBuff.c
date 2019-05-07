/*
 * CFile1.c
 *
 * Created: 5/4/2019 9:27:07 PM
 *  Author: natha
 */ 
#include <asf.h>
#include "RingBuff.h"

//the user initializes a p_bstru variable and passes it into the buff init and they can use the below functions to store data in it.
void u16BuffInit(p_bstru rstru)
{
	rstru=malloc(sizeof(struct uint16RingBuff));
	rstru->lastItem=BUFSIZE;
	//initializes all items to zero
	rstru->data=malloc(sizeof(uint16_t)*BUFSIZE);
	for(int i=0;i<BUFSIZE;i++)
	{
		rstru->data[i]=0;
	}
	
}
//adds an item to the ring buffer and increments last item variable
void putu16(p_bstru d_struct,uint16_t data)
{
	d_struct->lastItem=(d_struct->lastItem+1)%BUFSIZE;
	d_struct->data[d_struct->lastItem]=data;
}
//gets item starting at most recent index and going back
uint16_t getu16(p_bstru d_struct,int16_t index)
{
	index=((int16_t)d_struct->lastItem)-index;
	//wraps around if index is greater than the position of the last item
	while(index<0)
	{
		index+=BUFSIZE;
	}	
	return d_struct->data[index];
}
//adds the N most recently added items to an array
void array_recent(p_bstru bufStru,uint16_t * fRec,uint8_t N)
{
	for(uint8_t i=0;i++<N;i++)
	{
		fRec[i]=getu16(bufStru,i);
	}
}