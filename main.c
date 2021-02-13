/*
 * main.c
 *
 *  Created on: 11.02.2021
 *      Author: Yassine.O
 */
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "StMgApi.h"
#include"defines.h"

int main()
{

	char temp_text[40];
	if (FIFO_init(&Student_buf,st ,50) == FIFO_no_error)
	{
		DPRINTF("\n FIFO init succeded");
	}
	else
	{
		DPRINTF("\n FIFO init failed");
	}
	DPRINTF("\n Welcome to the Student Management System\n");

	while(1)
	{
		DPRINTF("\nChoose the Task that you want to perform");
		DPRINTF("\n1. Add the Student Details Manually");
		DPRINTF("\n2. Add the Student Details from Text File");
		DPRINTF("\n3. Find the Student Details By Roll Number");
		DPRINTF("\n4. Find the Student Details By First Name");
		DPRINTF("\n5. Find the Student Details By Course Id");
		DPRINTF("\n6. Find the Total number of Students");
		DPRINTF("\n7. Delete the Students Details By Roll Number");
		DPRINTF("\n8. Update the Students Details By Roll Number");
		DPRINTF("\n9. Show all information");
		DPRINTF("\n10. To Exit");
		DPRINTF("\nEnter your choice to perform the task: ");
		safe_gets(temp_text);
		switch(atoi(temp_text))
		{
		case 1:
			add_student_manually();
			break;
		case 2:
			add_student_file();
			break;
		case 3:
			find_rl();
			break;
		case 4:
			find_fn();
			break;
		case 5:
			find_c();
			break;
		case 6:
			tot_s();
			break;
		case 7:
			del_s();
			break;
		case 8:
			up_s();
			break;
		case 9:
			show_s();
			break;
		case 10:
			exit(0);
			break;
		default:
			DPRINTF("Bad Choice Please choose a Task from the list \n");
		}
	}

}
