/*
 * FIFO.h
 *
 *  Created on: 10.02.2021
 *      Author: Yassine.O
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "stdio.h"
#include <stdint.h>

#include "defines.h"
// USER Configuration


//FIFO data types




//FIFO APIs
FIFO_Buf_Status FIFO_init( FIFO_Buf_t* fifo, element_type* buf, uint32_t length);
FIFO_Buf_Status FIFO_enqueue( FIFO_Buf_t* fifo, element_type item);
FIFO_Buf_Status FIFO_dequeue( FIFO_Buf_t* fifo, element_type* item);
FIFO_Buf_Status FIFO_IS_FULL( FIFO_Buf_t* fifo);
void FIFO_print(FIFO_Buf_t* fifo);


#endif /* FIFO_H_ */
