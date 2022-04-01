// 181527590_190322170_a04_q2.c.txt
// Shaan Bhatia - Github ID: @shaanbhatia
// mera fares
// Github URL:

--------------------------------------------------------------------------------------------------------------------------------------------------
Create a program using Best-Fit algorithm for contiguous memory allocation to repond to request for a contiguous block of memory, release of a
contiguous block of memory and report the regions of free and allocated memory
--------------------------------------------------------------------------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX_ID 100

struct Node *top;
struct Node *block;
struct Node *temp;

char req[3];
char proc[3];
int last;
int space;

struct Node{
	int freespace;
	int start;
	int end;
	struct Node *next;
	char pid[MAX_ID];
};

int main(int argc, char *argv[]){

}

void BestFit(){

}

void Request(){

}

void Release(){

}

void Report(){
  
  temp = top;
  printf("avaliable space left: %d\n", top->freespace);
  while (temp->next != NULL){
	  printf("Addresses [%d : %d] Process %s\n", temp->next->start, temp->next->end, temp->next->pid);
	  temp = temp->next;
  }

}
