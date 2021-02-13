/*
 * defines.h
 *
 *  Created on: 12.02.2021
 *      Author: Yassine.O
 */

#ifndef DEFINES_H_
#define DEFINES_H_
#include <stdio.h>

#ifndef DPRINTF
#define DPRINTF(...) 	{fflush(stdout); fflush(stdin); printf(__VA_ARGS__); fflush(stdout); fflush(stdin);}
#endif

#ifndef safe_gets
#define safe_gets(...) 	fgets(__VA_ARGS__, sizeof(__VA_ARGS__), stdin);
#endif
// Type definitions
typedef struct {
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[5];
}sinfo_t;
//select the element type (uint8_t, uint26_t, uint32_t,...)
#define element_type sinfo_t
// create buffer
#define width 50
element_type st[width];
typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* tail;
	element_type* head;
}FIFO_Buf_t;

FIFO_Buf_t Student_buf;

typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}FIFO_Buf_Status;


#endif /* DEFINES_H_ */
