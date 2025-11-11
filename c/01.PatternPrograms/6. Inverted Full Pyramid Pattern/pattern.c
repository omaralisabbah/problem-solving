# include <stdio.h>

/*
	It is a 180° flipped version of the Full Pyramid Pattern we discussed earlier.
	We can see this as the combination of the Inverted Left Half and Inverted Right Half Pyramid Pattern we discussed earlier.
*/

int main()
{
	printf("6. Inverted Full Pyramid Pattern \n");
	printf("----------------------------- \n");

	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2*i; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * (rows - i)-1; k++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("----------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * i; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf("%i ", i+1);
		}
		printf("\n");
	}

	printf("----------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 2 * i; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * (rows - i) - 1; k++) {
			printf("%c ", 65+i);
		}
		printf("\n");
	}

	return 0;
}