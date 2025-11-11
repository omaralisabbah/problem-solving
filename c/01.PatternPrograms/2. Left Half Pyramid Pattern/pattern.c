# include <stdio.h>

/*
	The Left Half Pyramid looks like a right-angled triangle with its hypotenuse facing the left.
	We can also print this pattern using a character, alphabets, or numbers.
*/

int main()
{
	printf("2. Left Half Pyramid Pattern \n");
	printf("---------------------------- \n");
	
	int rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2* (rows - i)-1; k++) { // -1 = star place
			printf(" ");
		}
		for (int j = 0; j <= i; j++) {
			printf("* ");
		}
		printf("\n");
	}

	printf("---------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) { // -1 = star place
			printf(" ");
		}
		for (int j = 1; j <= i+1; j++) {
			printf("%d ", j);
		}
		printf("\n");
	}

	printf("---------------------------- \n");

	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < 2 * (rows - i) - 1; k++) { // -1 = star place
			printf(" ");
		}
		for (int j = 1; j <= i + 1; j++) {
			printf("%c ", 64 + j);
		}
		printf("\n");
	}
	return 0;
}