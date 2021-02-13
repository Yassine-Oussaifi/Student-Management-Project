/*
 * Student_Management_APIs.c
 *
 *  Created on: 11.02.2021
 *      Author: Yassine.O
 */
// Helper functions
#include "StMgApi.h"
// Helper functions
int parseLine(char* buf,sinfo_t* reconstructedStudent)
{
	char temp[50];
	int i,j,step=0,FileEndReached=0;;
	for (i=0, j=0; i<250; i++, j++)
	{
		switch(step)
		{
			case 0:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->roll= atoi(temp);
					step++;
					j=-1;
					break;
				}
			case 1:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					strcpy(reconstructedStudent->fname, temp);
					step++;
					j=-1;
					break;
				}
			case 2:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					strcpy(reconstructedStudent->lname, temp);
					step++;
					j=-1;
					break;
				}
			case 3:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->GPA= atof(temp);
					step++;
					j=-1;
					break;
				}
			case 4:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->cid[0]= atoi(temp);
					step++;
					j=-1;
					break;
				}
			case 5:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->cid[1]= atoi(temp);
					step++;
					j=-1;
					break;
				}
			case 6:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->cid[2]= atoi(temp);
					step++;
					j=-1;
					break;
				}
			case 7:
				if (buf[i]!= ' ')
				{
					temp[j]=buf[i];
					break;
				}
				else
				{
					temp[j]='\0';
					reconstructedStudent->cid[3]= atoi(temp);
					step++;
					j=-1;
					break;
				}
			case 8:
				if (buf[i] == EOF)
				{
					temp[j]='\0';
					reconstructedStudent->cid[4]= atoi(temp);
					i=250;
					FileEndReached=1;
					break;
				}
				else if(buf[i] == '\n')
				{
					temp[j]='\0';
					reconstructedStudent->cid[4]= atoi(temp);
					i=250;
					FileEndReached=0;
					break;
				}
				else
				{
					temp[j]=buf[i];
					break;
				}
		}
	}
	return FileEndReached;
}
void Show_buffer_health()
{
	DPRINTF("\n[INFO] The total number of Student is %u", Student_buf.count);
	DPRINTF("\n[INFO] You can add up to %u Students", Student_buf.length);
	DPRINTF("\n[INFO] You can add %u more students", (Student_buf.length - Student_buf.count));
}
void print_student(sinfo_t* student)
{
	DPRINTF("\n Student first name: %s", student->fname);
	DPRINTF("\n Student last name: %s", student->lname);
	DPRINTF("\n Student roll number: %d", student->roll);
	DPRINTF("\n Student GPA number: %.2f", student->GPA);
	DPRINTF("\n The course ID are: %d", student->cid[0]);
	DPRINTF("\n The course ID are: %d", student->cid[1]);
	DPRINTF("\n The course ID are: %d", student->cid[2]);
	DPRINTF("\n The course ID are: %d", student->cid[3]);
	DPRINTF("\n The course ID are: %d", student->cid[4]);
}
 int check_roll_exist(int roll, FIFO_Buf_t* fifo)
 {
	 if (fifo->count)
	 {
		 sinfo_t* pCurrentStudent= (sinfo_t*) fifo->tail;

		 while(pCurrentStudent->roll != roll)
		 {
			 if (pCurrentStudent == (sinfo_t*) fifo->head)
			 {
				 return 0;
			 }
			 else
			 {
				 pCurrentStudent++;
			 }
		 }
		 return 1;
	 }
	 return 0;
 }
 sinfo_t* search_roll_exist(int roll, FIFO_Buf_t* fifo)
  {
 	 if (fifo->count)
 	 {
 		 sinfo_t* pCurrentStudent= (sinfo_t*) fifo->tail;

 		 while(pCurrentStudent->roll != roll)
 		 {
 			 if (pCurrentStudent == (sinfo_t*) fifo->head-1)
 			 {
 				 return NULL;
 			 }
 			 else
 			 {
 				 pCurrentStudent++;
 			 }
 		 }
 		 return pCurrentStudent;
 	 }
 	 return NULL;
  }
//APIs Implementation

void add_student_file()
{
	FILE *fp;
	sinfo_t ReconstructedStudent;
	char temp_text[250];
	int status, buf_status;
    fp = fopen("log.txt", "r");
    if ( fp == NULL )
    {
    	 DPRINTF("\n---------------------------------------");
         printf( "\n[ERROR] Cannot open log file");
         return;
     }
    DPRINTF("\n---------------------------------------");
    do
    {
    	fgets(temp_text, 250, (FILE*) fp);
    	status = parseLine(temp_text,&ReconstructedStudent);
    	if (!check_roll_exist(ReconstructedStudent.roll,&Student_buf))
    	{
    		buf_status = FIFO_enqueue(&Student_buf, ReconstructedStudent);
    		if (buf_status == FIFO_no_error)
    		{
    			DPRINTF("\n[INFO] Roll number %d saved Successfully",ReconstructedStudent.roll);
    		}
    		else if(buf_status == FIFO_full)
    		{
    			DPRINTF("\n[ERROR] Students Buffer is Full");
    			break;
    		}
    		else
    		{
    			DPRINTF("\n[ERROR] Students Buffer is Not initialized");
    			break;
    		}
    	}
    	else
    	{
    		DPRINTF("\n[ERROR] ROLL Number %d is already taken",ReconstructedStudent.roll);
    	}
    }while(! feof( fp ));
    fclose(fp);
    DPRINTF("\n[INFO] Student Details is added Successfully");
    DPRINTF("\n---------------------------------------");
    Show_buffer_health();
}

void add_student_manually()
{
	char temp_text[50];
	int temp;
	DPRINTF("---------------------------------------");
	DPRINTF("\n Add the Student Details");
	DPRINTF("\n---------------------------------------");
	DPRINTF("\nEnter the Roll Number: ");
	safe_gets(temp_text);
	temp = atoi(temp_text);
	if (check_roll_exist(temp, &Student_buf))
	{
		DPRINTF("\n[ERROR] ROLL Number %d is already taken",temp);
		return;
	}
	else
	{
		sinfo_t tempStudent;
		int i,buf_status = 0;
		tempStudent.roll= temp;
		DPRINTF("Enter the first name of student: ");
		safe_gets(temp_text);
		 for (i=0; i<strlen(temp_text);i++)
		 {
			 if (temp_text[i]=='\n')
			 {
				 temp_text[i]='\0';
			 }
		 }
		 strcpy(tempStudent.fname, temp_text);
		 DPRINTF("Enter the last name of student: ");
		 safe_gets(temp_text);
		 for (i=0; i<strlen(temp_text);i++)
		 {
			 if (temp_text[i]=='\n')
			 {
				 temp_text[i]='\0';
			 }
		 }
		 strcpy(tempStudent.lname, temp_text);
		DPRINTF("Enter the GPA you obtained: ");
		safe_gets(temp_text);
		tempStudent.GPA =atof(temp_text);
		DPRINTF("Enter the Course ID of each Course");
		DPRINTF("\nCourse 1 id: ");
		safe_gets(temp_text);
		tempStudent.cid[0] =atoi(temp_text);
		DPRINTF("Course 2 id: ");
		safe_gets(temp_text);
		tempStudent.cid[1] =atoi(temp_text);
		DPRINTF("Course 3 id: ");
		safe_gets(temp_text);
		tempStudent.cid[2] =atoi(temp_text);
		DPRINTF("Course 4 id: ");
		safe_gets(temp_text);
		tempStudent.cid[3] =atoi(temp_text);
		DPRINTF("Course 5 id: ");
		safe_gets(temp_text);
		tempStudent.cid[4] =atoi(temp_text);
		buf_status = FIFO_enqueue(&Student_buf, tempStudent);
		if (buf_status == FIFO_no_error)
		{
			DPRINTF("[INFO] Student Details is added Successfully");
			DPRINTF("\n---------------------------------------");
			Show_buffer_health();
		}
		else if(buf_status == FIFO_full)
		{
			DPRINTF("\n[ERROR] Students Buffer is Full");
		}
		else
		{
			DPRINTF("\n[ERROR] Students Buffer is Not initialized");
		}
	}


}
void find_rl()
{
	char temp_text[50];
	int roll = 0;
	DPRINTF("\nEnter the Roll Number of the student:");
	safe_gets(temp_text);
	roll = atoi(temp_text);
	sinfo_t* pFoundRoll= search_roll_exist(roll, &Student_buf);
	if (pFoundRoll!=NULL)
	{
		DPRINTF("The student details are:");
		print_student(pFoundRoll);
		DPRINTF("\n---------------------------------------");
	}
	else
	{
		DPRINTF("[ERROR] Roll Number %d not found",roll );
		DPRINTF("\n---------------------------------------");
	}

}
void find_fn()
{
	char temp_text[50];
	char found =0;
	int i;
	DPRINTF("\nEnter the First Name of the student:");
	safe_gets(temp_text);
	 for (i=0; i<strlen(temp_text);i++)
	 {
		 if (temp_text[i]=='\n')
		 {
			 temp_text[i]='\0';
		 }
	 }
	if (Student_buf.count)
	 {
		 sinfo_t* pCurrentStudent= (sinfo_t*) Student_buf.tail;

		 while(pCurrentStudent != (sinfo_t*) Student_buf.head)
		 {
			 if (strcmp(pCurrentStudent->fname, temp_text) == 0)
			 {
				DPRINTF("\nThe student details are:");
				print_student(pCurrentStudent);
				DPRINTF("\n---------------------------------------");
				found =1;
				pCurrentStudent++;
			 }
			 else
			 {
				 pCurrentStudent++;
			 }
		 }
		 if (found == 0)
		 {
			 for (i=0; i<strlen(temp_text);i++)
			 {
				 if (temp_text[i]=='\n')
				 {
					 temp_text[i]='\0';
				 }
			 }
			 DPRINTF("[ERROR] First name %s not found", temp_text);
			 DPRINTF("\n---------------------------------------");
		 }
	 }
	else
	{
		DPRINTF("\nThe list is Empty");
		DPRINTF("\n---------------------------------------");
	}
}
void find_c()
{
	char temp_text[50];
	unsigned int found =0;
	int ID = 0;
	DPRINTF("\nEnter the course ID:");
	safe_gets(temp_text);
	ID = atoi(temp_text);
	if (Student_buf.count)
	 {
		 sinfo_t* pCurrentStudent= (sinfo_t*) Student_buf.tail;

		 while(pCurrentStudent != (sinfo_t*) Student_buf.head)
		 {

			 if ((pCurrentStudent->cid[0]==ID)||(pCurrentStudent->cid[1]==ID)||(pCurrentStudent->cid[2]==ID)||(pCurrentStudent->cid[3]==ID)||(pCurrentStudent->cid[4]==ID))
			 {
				DPRINTF("\nThe student details are:");
				print_student(pCurrentStudent);
				DPRINTF("\n---------------------------------------");
				found ++;
				pCurrentStudent++;
			 }
			 else
			 {
				 pCurrentStudent++;
			 }
		 }
		 if (found == 0)
		 {
			 DPRINTF("[ERROR] Course ID %d not found", ID);
			 DPRINTF("\n---------------------------------------");
		 }
		 else
		 {
			 DPRINTF("[\nINFO] Total Number of Students Enrolled: %u", found);
			 DPRINTF("\n---------------------------------------");
		 }
	 }
	else
	{
		DPRINTF("\nThe list is Empty");
		DPRINTF("\n---------------------------------------");
	}
}
void tot_s()
{
	DPRINTF("\n---------------------------------------");
	Show_buffer_health();
}
void del_s()
{
	char temp_text[50];
	int roll = 0;
	DPRINTF("\nEnter the Roll Number to be deleted:");
	safe_gets(temp_text);
	roll = atoi(temp_text);
	sinfo_t* pFoundRoll= search_roll_exist(roll, &Student_buf);
	if (pFoundRoll==NULL)
	{
		DPRINTF("[ERROR] Roll Number %d not found",roll );
		DPRINTF("\n---------------------------------------");
	}
	else
	{
		if (pFoundRoll == (sinfo_t*) Student_buf.tail)
		{
			Student_buf.count--;
			Student_buf.tail++;
		}
		else
		{
			for (;pFoundRoll < (sinfo_t*) Student_buf.head-1;pFoundRoll++)
			{
			*pFoundRoll = * (pFoundRoll+1);
			}
			Student_buf.head--;
			Student_buf.count--;
		}
		DPRINTF("[INFO] The Roll Number is removed Successfully");
	}
	return;
}
void up_s()
{
	char temp_text[50];
	int i,roll = 0;
	DPRINTF("\nEnter the Roll number to update the entry:");
	safe_gets(temp_text);
	roll = atoi(temp_text);
	sinfo_t* pFoundRoll= search_roll_exist(roll, &Student_buf);
	if (pFoundRoll==NULL)
	{
		DPRINTF("[ERROR] Roll Number %d not found",roll );
		DPRINTF("\n---------------------------------------");
	}
	else
	{
		DPRINTF("1. first name");
		DPRINTF("\n2. last name");
		DPRINTF("\n3. roll no");
		DPRINTF("\n4. GPA");
		DPRINTF("\n5. courses\n");
		safe_gets(temp_text);
		switch (atoi(temp_text))
		{
		case 1:
			DPRINTF("Enter the new first name:");
			safe_gets(temp_text);
			for (i=0; i<strlen(temp_text);i++)
			{
				if (temp_text[i]=='\n')
				{
					temp_text[i]='\0';
				}
			}
			strcpy(pFoundRoll->fname, temp_text);
			DPRINTF("[INFO] UPDATED SUCCESSFULLY");
			 break;
		case 2:
			DPRINTF("Enter the new last name:");
			safe_gets(pFoundRoll->lname);
			DPRINTF("[INFO] UPDATED SUCCESSFULLY");
			break;
		case 3:
			DPRINTF("Enter the new roll no:");
			safe_gets(temp_text);
			pFoundRoll->roll = atoi(temp_text);
			DPRINTF("[INFO] UPDATED SUCCESSFULLY");
			break;
		case 4:
			DPRINTF("Enter the new GPA:");
			safe_gets(temp_text);
			pFoundRoll->GPA = atof(temp_text);
			DPRINTF("[INFO] UPDATED SUCCESSFULLY");
			break;
		case 5:
			DPRINTF("Enter the Course ID of each Course");
			DPRINTF("\nCourse 1 id: ");
			safe_gets(temp_text);
			pFoundRoll->cid[0] =atoi(temp_text);
			DPRINTF("Course 2 id: ");
			safe_gets(temp_text);
			pFoundRoll->cid[1] =atoi(temp_text);
			DPRINTF("Course 3 id: ");
			safe_gets(temp_text);
			pFoundRoll->cid[2] =atoi(temp_text);
			DPRINTF("Course 4 id: ");
			safe_gets(temp_text);
			pFoundRoll->cid[3] =atoi(temp_text);
			DPRINTF("Course 5 id: ");
			safe_gets(temp_text);
			pFoundRoll->cid[4] =atoi(temp_text);
			DPRINTF("[INFO] UPDATED SUCCESSFULLY");
			break;
		default:
			DPRINTF("[ERROR] WRONG CHOICE");
		}
	}
	return;
}
void show_s()
{
	 if (Student_buf.count)
	 {
		 sinfo_t* pCurrentStudent= (sinfo_t*) Student_buf.tail;

		 while(pCurrentStudent < (sinfo_t*) Student_buf.head)
		 {
			 if (pCurrentStudent == (sinfo_t*) Student_buf.head -1)
			 {
				 DPRINTF("\n---------------------------------------");
				 print_student(pCurrentStudent);
				 DPRINTF("\n---------------------------------------");
				 return;
			 }
			 else
			 {
				 DPRINTF("\n---------------------------------------");
				 print_student(pCurrentStudent);
				 pCurrentStudent++;
			 }
		 }
		 return;
	 }
	 DPRINTF("\n Students list is Empty")
	 DPRINTF("\n---------------------------------------");
	 return;
 }
