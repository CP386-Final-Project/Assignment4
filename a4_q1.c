// 181527590_###_a04_q1.c.txt
// Shaan Bhatia - Github ID: @shaanbhatia
// mir
// Github URL:

/*///////////////////////////////////////////////////////////////////////
 / Write a multi-threaded program that implements the banker's algorithm /
 ///////////////////////////////////////////////////////////////////////*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

int readFile(char *fileName); // function to read from file

typedef struct thread {
	char tid[1]; //id of the thread as read from file
} Thread;

int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("Not enough arguments (need available resource quantities)\n");
		printf("Exit with error code -1\n");
		return -1;
	}
	printf("Main function working: argc: %d\n", argc);
	readFile("sample4_in.txt");
	return 0;
}

int readFile(char *fileName) {

	FILE *in = fopen(fileName, "r");
	if (!in) {
		printf("Error in opening input file. Exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';
	while (!feof(in)) {
		char line[100];
		if (fgets(line, 100, in) != NULL) {
			strncat(fileContent, line, strlen(line));
		}
	}
	fclose(in);

	int i, j, count;
	count = 0;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 8; j++) {
			printf("%c", fileContent[count]);
			count++;
		}
		printf("\n");
		count++;
	}

	return 0;
}
