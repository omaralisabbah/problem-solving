# include <stdio.h>

/*
	This pattern is also similar to the Diamond Pattern but without the inner
	elements such that it appears hollow inside
*/

int main()
{
	printf("13. Hollow Diamond Pattern \n");
	printf("-------------------------- \n");

	int rows = 5;
	for (int i = 0; i < 2 * rows - 1; i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) - 1;
		}
		else {
			comp = 2 * (i - rows + 1) + 1;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * rows - comp; k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1)) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("-------------------------- \n");

	for (int i = 0; i < 2 * rows - 1; i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) - 1;
		}
		else {
			comp = 2 * (i - rows + 1) + 1;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * rows - comp; k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1)) {
				printf("%i ", i+1);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("-------------------------- \n");

	for (int i = 0; i < 2 * rows - 1; i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) - 1;
		}
		else {
			comp = 2 * (i - rows + 1) + 1;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}

		for (int k = 0; k < 2 * rows - comp; k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1)) {
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