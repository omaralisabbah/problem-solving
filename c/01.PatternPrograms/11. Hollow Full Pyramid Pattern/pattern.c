# include <stdio.h>

/*
	In the Hollow Pyramid pattern, we only have to print the boundary of the full pyramid.
*/

int main()
{
	printf("11. Hollow Full Pyramid Pattern \n");
	printf("------------------------------- \n");

	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			if ((j == 0) || (j == 2 * i) || (i == rows - 1)) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("------------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) { // ex : third row (2*2+1=5) stars
			if ((j == 0) || (j == 2 * i) || (i == rows - 1)) {
				printf("%i ", i+1);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("------------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) { // ex : third row (2*2+1=5) stars
			if ((j == 0) || (j == 2 * i) || (i == rows - 1)) {
				printf("%c ", 65+i);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	return 0;
}