#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void create2DArray(int size, char array[]) {
	int R = floor(sqrt(size));
	int C = ceil(sqrt(size));
	if (R * C < size) {
		R = R + 1;
	}
	char array2D[R][C];
	int k = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (k < strlen(array)) {
				array2D[i][j] = array[k];
			}
			k++;
		}
	}
	k = 0;

	char array1D[size + C];

	for (int j = 0; j < C; j++) {
		for (int i = 0; i < R; i++) {
			if (array2D[i][j] != '\0') {
				array1D[k] = array2D[i][j];
				k++;
			}
		}
		array1D[k] = ' ';
		k++;
	}
	for (int i = 0; i < size + C; i++) {
		printf("%c", array1D[i]);
	}
}

void encrypt(char str[]) {
	int N = 0;
	int j = 0;
	char arrayNoSpace[81];
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != ' ') {
			arrayNoSpace[j++] = str[i];
			N++;
		}
	}
	create2DArray(N, arrayNoSpace);
}

typedef struct {
	int day;
	int month;
	int year;
} Date;
typedef struct {
	int id;
	char firstname[20];
	char lastname[20];
	char result[9];
	Date dt;
} Member;

int readresults(Member members[]) {
	FILE *pcr;
	pcr = fopen("pcr_results.txt", "r");

	if (pcr == NULL) {
		printf("Problem opening files");
		return 1;
	}
	printf("Files opened successfully\n");

	int lines = 0;

	do {

		fscanf(pcr, "%d %s %s %s %d %d %d\n", &members[lines].id,
				members[lines].firstname, members[lines].lastname,
				members[lines].result, &members[lines].dt.day,
				&members[lines].dt.month, &members[lines].dt.year);

		lines++;

	} while (!feof(pcr));

	fclose(pcr);

	return lines;
}

void encryptintofile(int size, char array[]) {

	int R = floor(sqrt(size));
	int C = ceil(sqrt(size));
	if (R * C < size) {
		R = R + 1;

	}
	char array2D[R][C];
	int k = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (k < size && array[k] != '\n') {
				array2D[i][j] = array[k];
				k++;

			} else {
				array2D[i][j] = '\0'; // reduce garbage chars at the at of each line/row
			}
		}
	}
	k = 0; // to use 'k' in the next loop

	char array1D[size + C];

	for (int j = 0; j < C; j++) {
		for (int i = 0; i < R; i++) {
			if (array2D[i][j] != '\0') {
				array1D[k] = array2D[i][j];
				k++;
			} else {
				array2D[i][j] = '\0';
			}
		}
		array1D[k] = ' ';

		k++;

	}


	FILE * output;
	output = fopen("encrypted_results.txt", "a");

	for (int i = 0; i < size+C; i++) {
		fprintf(output, "%c", array1D[i]);

	}fprintf(output,"\n");

	for (int i = 0; i < size+C; i++) {
			printf("%c", array1D[i]);

		}printf("\n\n");

	fclose(output);

}
void arrayNospace(char line[]) {
	char arrayNoSpace[500];
	int N = 0;
	int j = 0;
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] != ' ') {
			arrayNoSpace[j++] = line[i];
			if (line[i] != '\n') {
				N++;
			}
		}

	}
	encryptintofile(N, arrayNoSpace);

}


int main() {

	 printf("------\n");
	 printf("TASK 1\n");
	 printf("------\n");
	 char S[500] = "i love CSCI 151";
	 encrypt(S);


	printf("\n\n\n------\n");
	printf("TASK 2\n");
	printf("------\n");

	Member members[100];

	int number = readresults(members);
	printf("The number of lines in the file is %i", number);

	char line[500];
	FILE *pcr;
		pcr = fopen("pcr_results.txt", "r");


		do {
	     fgets(line, 500, pcr);
	     arrayNospace(line);

		} while (!feof(pcr));
		fclose(pcr);



	return 0;
}
