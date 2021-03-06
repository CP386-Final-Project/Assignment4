// 181527590_190322170_a04_q1.c
// Shaan Bhatia - Github ID: @shaanbhatia
// Mera Fare - GitHub ID @merafare
// Github URL: https://github.com/CP386-Final-Project/Assignment4.git

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
#include <ctype.h>

int* create_arr(int m) {
	int *arr = (int*) malloc(m * sizeof(int*));
	return arr;
}

int** create_twod_arr(int n, int m) {
	int **twod_arr = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		twod_arr[i] = (int*) malloc(m * sizeof(int));
	}
	return twod_arr;
}

void destroyAr(int **arr) {
	free(*arr);
	free(arr);
}

void display_status(int *ava_r, int **max_r, int **all_r, int **need_r, int m,
		int n) {
	printf("Available Resources: \n");
	for (int i = 0; i < m; i++) {
		printf("%d ", ava_r[i]);
	}
	printf("\n");
	printf("Maximum Resources: \n");
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < m; b++) {
			printf("%d ", max_r[a][b]);
		}
		printf("\n");
	}
	printf("Allocated Resources: \n");
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < m; b++) {
			printf("%d ", all_r[a][b]);
		}
		printf("\n");
	}
	printf("Need Resources: \n");
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < m; b++) {
			printf("%d ", need_r[a][b]);
		}
		printf("\n");
	}
}

//returns 0 if arr1 <= arr2
int compare_arrays(int *arr1, int *arr2, int size) {
	int flag = 0;
	for (int i = 0; i < size; i++) {
		if (arr1[i] > arr2[i]) {
			flag = 1;
		}
	}
	return flag;
}

// Returns safe sequence
int* is_safe(int *ava_r, int **all_r, int **need_r, int m, int n, int cust_id,
		int *request_arr) {

	// Initialize work
	int work[m];
	for (int i = 0; i < m; i++) {
		work[i] = ava_r[i];
	}
	// Initialize fin
	int fin[n];
	for (int i = 0; i < n; i++) {
		fin[i] = 0;
	}

	// Initialize safe sequence
	int *safe_seq = create_arr(n);

	// Safety Algorithm
	int all_false = 1;
	int safe_count = 0;
	while (all_false == 1) {
		for (int i = 0; i < n; i++) {
			if (compare_arrays(need_r[i], work, m) == 0) {
				fin[i] = 1;
				for (int k = 0; k < m; k++) {
					work[k] += all_r[i][k];
				}
				safe_seq[safe_count] = i;
				safe_count++;
			}
		}
		for (int o = 0; o < n; o++) {
			if (fin[o] == 1) {
				all_false = 0;
			}
		}
	}

	return safe_seq;
}
// Returns 1 upon success
int resource_req(int cust_id, int *request_arr, int **need_r, int *ava_r,
		int **all_r, int m) {

	if (compare_arrays(request_arr, need_r[cust_id], m) != 0) {
		return 0;
	}
	if (compare_arrays(request_arr, ava_r, m) != 0) {
		return 0;
	}

	for (int i = 0; i < m; i++) {
		ava_r[i] = ava_r[i] - request_arr[i];
	}
	for (int i = 0; i < m; i++) {
		all_r[cust_id][i] = all_r[cust_id][i] + request_arr[i];
	}
	for (int i = 0; i < m; i++) {
		need_r[cust_id][i] = need_r[cust_id][i] - request_arr[i];
	}
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Not enough arguments (need available resource quantities)\n");
		printf("Exit with error code -1\n");
		return -1;
	}

	// Number of resource types
	int m = (argc - 1);

	// Available resources array
	int *ava_r = create_arr(m);

	// Initialize available resource array with command line arguments, and display them
	printf("Currently available resources: ");
	for (int i = 0; i < m; i++) {
		ava_r[i] = atoi(argv[i + 1]);
		printf("%d ", ava_r[i]);
	}
	printf("\n");

	// Read file to initialize customers
	// File checking
	FILE *in = fopen("sample4_in.txt", "r");
	if (!in) {
		printf("Error in opening input file. Exiting with error code -1\n");
	}

	// There will be n customers
	int n = 0;

	// Store file content in array
	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char*) malloc(((int) st.st_size + 1) * sizeof(char));
	while (!feof(in)) {
		char line[100];
		if (fgets(line, 100, in) != NULL) {
			strncat(fileContent, line, strlen(line));
			n++;
		}
	}
	fclose(in);

	// Initialize Max resource array
	int **max_r = create_twod_arr(n, m);

	// Put file content in 2D array
	int count = 0;
	char c[2] = { 0 };
	int i = 0, j = 0, k = 0;
	while (fileContent[count]) {
		if (isdigit(fileContent[count])) {
			c[k] = fileContent[count];
			k++;
		}
		if (fileContent[count] == ',' || fileContent[count] == '\n') {
			max_r[i][j] = atoi(c);
			k = 0;
			for (int z = 0; z < k + 1; z++) {
				c[z] = '\0';
			}
			j++;
			if (j == m) {
				j = 0;
				i++;
			}
		}
		count++;
	}
	max_r[i][j] = atoi(c);

	// Display maximum resources 2D array
	printf("Maximum resources from file:\n");
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < m; b++) {
			printf("%d ", max_r[a][b]);
		}
		printf("\n");
	}

	// Initialize allocation resource array
	int **all_r = create_twod_arr(n, m);
	for (int c = 0; c < n; c++) {
		for (int d = 0; d < m; d++) {
			all_r[c][d] = 0;
		}
	}

	// Initialize need resource array
	int **need_r = create_twod_arr(n, m); // max - allocation
	for (int c = 0; c < n; c++) {
		for (int d = 0; d < m; d++) {
			need_r[c][d] = max_r[c][d];
		}
	}

	// Main loop
	char input[10];
	const char space[2] = " ";
	int is_safe_check = 0;
	int cust_id;
	int *request_arr = create_arr(m);
	while (strcmp(input, "Exit\n") != 0) {
		printf("Enter a value: ");
		fgets(input, 13, stdin);

		// Display Status
		if (strcmp(input, "Status\n") == 0) {
			display_status(ava_r, max_r, all_r, need_r, m, n);
		}

		// Request resources
		if (input[0] == 'R') {
			if (input[1] == 'Q') {
				strtok(input, space); // For RQ
				cust_id = atoi(strtok(NULL, space)); // For Customer ID
				request_arr[0] = atoi(strtok(NULL, space));
				request_arr[1] = atoi(strtok(NULL, space));
				request_arr[2] = atoi(strtok(NULL, space));
				request_arr[3] = atoi(strtok(NULL, space));
				int *safe_seq = is_safe(ava_r, all_r, need_r, m, n, cust_id,
						request_arr);

				for (int y = 0; y < n; y++) {
					is_safe_check += safe_seq[y];
				}
				if (is_safe_check != ((n / 2) * (4))) {
					resource_req(cust_id, request_arr, need_r, ava_r, all_r, m);
					printf("State is safe, and request is satisfied\n");
				} else {
					printf("State is not safe\n");
				}

			}
		}
	}

	// Free up array space
	destroyAr(max_r);
	return 0;
}
