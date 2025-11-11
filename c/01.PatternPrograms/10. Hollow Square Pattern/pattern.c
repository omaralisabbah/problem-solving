# include <stdio.h>

/*
	
*/

int main()
{
	printf("10. Hollow Square Pattern \n");
	printf("------------------------- \n");

	int rows = 5;
	for (int i = 1; i <= rows; i++) {
		for (int k = 0; k < rows; k++) {
			if ((rows - i + 1 == rows) || (rows - i == 0)) {
				printf("* ");
			}
			else {
				printf("*       *");
				break;
			}
		}
		printf("\n");
	}

	printf("------------------------- \n");

	for (int i = 1; i <= rows; i++) {
		for (int k = 0; k < rows; k++) {
			if ((rows - i+1 == rows) || (rows - i == 0)) {
				printf("%i ",i);
			}
			else {
				printf("%i       %i", i, i);
				break;
			}
		}
		printf("\n");
	}

	printf("------------------------- \n");

	for (int i = 1; i <= rows; i++) {
		for (int k = 0; k < rows; k++) {
			if ((rows - i + 1 == rows) || (rows - i == 0)) {
				printf("%c ", i+64);
			}
			else {
				printf("%c       %c", i + 64, i + 64);
				break;
			}
		}
		printf("\n");
	}

	return 0;
}