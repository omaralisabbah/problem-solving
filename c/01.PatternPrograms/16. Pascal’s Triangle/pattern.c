# include <stdio.h>

/*
	A Pascal’s Triangle is a triangular array of binomial coefficients where the n
	row contains the binomial coefficients C , C , C , ……. C . The following
	example demonstrates one of the methods using which we can print Pascal’s
	Triangle Pattern.

*/

int main()
{
	printf("16. Pascal’s Triangle \n");
	printf("--------------------- \n");
	
	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows - i; j++) {
			printf(" ");
		}
		for (int k = 0; k <= i; k++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("--------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows - i; j++) {
			printf(" ");
		}
		for (int k = 0; k <= i; k++) {
			printf("%i ", i+1);
		}
		printf("\n");
	}

	printf("--------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows - i; j++) {
			printf(" ");
		}
		for (int k = 0; k <= i; k++) {
			printf("%c ", i+65);
		}
		printf("\n");
	}

	return 0;
}