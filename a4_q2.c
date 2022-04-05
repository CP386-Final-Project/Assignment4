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

struct Node *top; //tracks available main memory
struct Node *block; //amount of space in memory
struct Node *temp; //traverse usage

char req[3];
char proc[3];
char alg_type[2];
int last;
int space;

struct Node {
	int freespace;
	int start;
	int end;
	struct Node *next;
	char pid[MAX_ID];
};

void bestfit(char pid[3], int space) {
	struct Node *newnode = (struct Node*) malloc(sizeof(struct Node));
	int smallest = 999999;
	int empty_space = 0;
	temp = top;

	while (temp->next != NULL) { //find smallest available space
		if (strcmp(temp->next->pid, "Unused") == 0 //if space big enough and unused
		&& temp->next->freespace >= space) {
			if (temp->next->freespace <= smallest) //track small space
				smallest = temp->next->freespace;
			//traversing
		} else
			temp = temp->next;
	}
	temp = top;

	while (temp->next != NULL) {
		if (temp->next->freespace == smallest) { //find small space
			top->freespace = top->freespace - space;

			strcpy(temp->next->pid, pid);
			temp->next->end = temp->next->start + space;

			empty_space = temp->next->freespace - space;
			if (empty_space > 0) {
				struct Node *newNode = (struct Node*) malloc(
						sizeof(struct Node));
				strcpy(newNode->pid, "Unused");
				newNode->freespace = empty_space;
				temp->next->freespace = space;
				newNode->start = temp->next->end + 1;
				newNode->end = newNode->start + empty_space;
				if (newNode->end > last)
					newNode->end = last;
				newNode->next = temp->next->next;
				temp->next->next = newNode;
			}
			return;

		} else
			temp = temp->next;
	}

	printf("There is no space to place process %s, of %dkb\n", pid, space);

}
void request(char pid[3], int space, char alg_type[2]) {

	if (strcmp("B", alg_type) == 0)
		bestfit(pid, space);
	else {
		printf("Try again\n");
		return;
	}
}
void release(char pid[3]) {

}

void report() {
	temp = top;

	printf("avaliable space left: %d\n", top->freespace);
	while (temp->next != NULL) {
		printf("Addresses [%d : %d] Process %s\n", temp->next->start,
				temp->next->end, temp->next->pid);
		temp = temp->next;
	}

}
int main(int argc, char *argv[]) {

	int memory = atoi(argv[1]);
	char input[128];
	printf("%d\n", memory);

//	printf("allocator>");
	fflush(stdout);

	if (read(0, input, 128) < 0)
		write(2, "an error occurred in the read.\n", 31);
	top = (struct Node*) malloc(sizeof(struct Node));

	block = (struct Node*) malloc(sizeof(struct Node));

	strcpy(top->pid, "error");
	top->start = -1;
	top->end = -1;
	top->freespace = memory;
	top->next = block;

	strcpy(block->pid, "unused");
	block->start = 0;
	block->end = memory;
	block->freespace = block->end - block->start;
	block->next = NULL;

	last = memory;

	while (input[0] != 'x') {
		if ((sscanf(input, '%s %s', req, proc)) < 0)
			write(2, "an error has occured\n", 31);

		if (strcmp("RQ", req) == 0) {
			sscanf(input, "successfully allocated %s %s %d %s", req, proc,
					&space, alg_type);
			request(proc, space, alg_type);
			// release memory command
		} else if (strcmp("RL", req) == 0) {
			sscanf(input, 'successfully allocated %s %s', req, proc);
			release(proc);
		} else if (strcmp('STAT', req) == 0) {
			report();
		} else { //for undisered command
			printf("This command is not recognized\n");
		}
//		Report();

		printf("allocator >");
		fflush(stdout);

	}

}
