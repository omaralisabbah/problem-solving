# include <stdio.h>

/*
	The Rhombus pattern is similar to the square pattern, just that we have to add spaces before each line and their count decreases progressively with rows.
*/

int main()
{
	printf("7. Rhombus Pattern \n");
	printf("------------------ \n");

	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2*(rows - i) - 1; j++) {
			printf(" ");
		}

		for (int k = 0; k <= rows; k++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("------------------ \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * (rows - i) - 1; j++) {
			printf(" ");
		}

		for (int k = 0; k <= rows; k++) {
			printf("%i ", i+1);
		}
		printf("\n");
	}

	printf("------------------ \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * (rows - i) - 1; j++) {
			printf(" ");
		}

		for (int k = 0; k <= rows; k++) {
			printf("%c ", i+65);
		}
		printf("\n");
	}

	return 0;
}