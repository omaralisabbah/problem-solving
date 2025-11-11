# include <stdio.h>

/*
	In Floyd’s Triangle pattern, instead of starting the sequence of the numbers
	from 1 in each row, we print consecutive natural numbers. We can also print this pattern for alphabet sequence.
*/

int main()
{
	printf("15. Floyd’s Triangle \n");
	printf("-------------------- \n");

	int rows = 5;
	int n = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d ", n++);
		}
		printf("\n");
	}

	printf("-------------------- \n");
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%c ", (49 + n++));
		}
		printf("\n");
	}



	return 0;
}