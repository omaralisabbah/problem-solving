# include <stdio.h>

/*
	This pattern is the 180° flipped version of the left half pyramid pattern we discussed earlier.
*/

int main()
{
	printf("5. Inverted Left Half Pyramid Pattern \n");
	printf("------------------------------------- \n");

	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * i; j++) {
			printf(" ");
		}
		for (int k = 0; k < rows - i; k++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("------------------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * i; j++) {
			printf(" ");
		}
		for (int k = 0; k < rows - i; k++) {
			printf("%i ", k+1);
		}
		printf("\n");
	}

	printf("------------------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * i; j++) {
			printf(" ");
		}
		for (int k = 0; k < rows - i; k++) {
			printf("%c ", k+65);
		}
		printf("\n");
	}

	return 0;
}