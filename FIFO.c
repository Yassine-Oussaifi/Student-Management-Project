/*
 * FIFO.c
 *
 *  Created on: 10.02.2021
 *      Author: Yassine.O
 */
#include "FIFO.h"
//FIFO APIs
FIFO_Buf_Status FIFO_init( FIFO_Buf_t* fifo, element_type* buf, uint32_t length)
{
	if(buf ==NULL)
		return FIFO_null;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;
	return FIFO_no_error;
}
FIFO_Buf_Status FIFO_enqueue( FIFO_Buf_t* fifo, element_type item)
{
	if(!fifo->base ||!fifo->tail ||!fifo->head)
		return FIFO_null;
	if(FIFO_IS_FULL(fifo) == FIFO_full)
		return FIFO_full;
	*(fifo->head) = item;
	fifo->count++;
	fifo->head++;
	return FIFO_no_error;
}
FIFO_Buf_Status FIFO_dequeue( FIFO_Buf_t* fifo, element_type* item)
{
	if(!fifo->base ||!fifo->tail ||!fifo->head)
		return FIFO_null;
	if (fifo->count == 0)
		return FIFO_empty;
	*item = *(fifo->tail);
	fifo->count--;
	fifo->tail++;
	return FIFO_no_error;
}
FIFO_Buf_Status FIFO_IS_FULL( FIFO_Buf_t* fifo)
{
	if(!fifo->base ||!fifo->tail ||!fifo->head)
				return FIFO_null;
	if (fifo->count == fifo->length)
		return FIFO_full;
	return FIFO_no_error;
}

