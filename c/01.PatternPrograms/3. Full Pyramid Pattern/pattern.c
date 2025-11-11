# include <stdio.h>

/*
	The Full Pyramid pattern looks similar to the Equilateral triangle.
	We can see this as the combination of the Left Half and Right Half pyramids patterns.
	The following example demonstrates how to print this pattern using alphabets, numbers, or a star (*).
*/

int main()
{
	printf("3. Full Pyramid Pattern \n");
	printf("----------------------- \n");
	
	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2*(rows - i)-1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) { // ex : third row (2*2+1=5) stars
			printf("* ");
		}
		printf("\n");
	}

	printf("----------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			printf("%d ", j+1);
		}
		printf("\n");
	}

	printf("----------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf(" ");
		}
		for (int j = 0; j < 2 * i + 1; j++) {
			printf("%c ", 65+j);
		}
		printf("\n");
	}

	return 0;
}