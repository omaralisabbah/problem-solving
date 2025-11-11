# include <stdio.h>

/*
	The right-half pyramid is nothing but a right-angle triangle whose hypotenuse is in the right direction.
	We can print the right half pyramid pattern using numbers, alphabets, or any other character like a star (*).
*/

int main()
{
	printf("1. Right Half Pyramid Pattern \n");
	printf("----------------------------- \n");
	
	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k <= i; k++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("----------------------------- \n");

	for (int i = 1; i <= rows; i++) {
		for (int k = 1; k <= i; k++) {
			printf("%i ", k);
		}
		printf("\n");
	}

	printf("----------------------------- \n");

	for (int i = 1; i <= rows; i++) {
		for (int k = 1; k <= i; k++) {
			printf("%c ", 64+k); // ascii characters starts from (64+1 = A)
		}
		printf("\n");
	}

	return 0;
}