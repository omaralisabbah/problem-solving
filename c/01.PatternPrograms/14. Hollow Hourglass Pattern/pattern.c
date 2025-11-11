# include <stdio.h>

/*
	The hollow hourglass is the pattern in which only the boundary of the hourglass pattern is visible.
*/

int main()
{
	printf("14. Hollow Hourglass Pattern \n");
	printf("---------------------------- \n");

	int rows = 5;
	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * i + 1;
		}
		else {
			comp = 2 * (2 * rows - i) - 3;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}
		for (int k = 0; k < (2 * rows - comp); k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1) || (i == 0) || (i == 2 * rows - 2)) {
				printf("* ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("---------------------------- \n");

	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * i + 1;
		}
		else {
			comp = 2 * (2 * rows - i) - 3;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}
		for (int k = 0; k < (2 * rows - comp); k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1) || (i == 0) || (i == 2 * rows - 2)) {
				printf("%i ", i+1);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	printf("---------------------------- \n");

	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * i + 1;
		}
		else {
			comp = 2 * (2 * rows - i) - 3;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}
		for (int k = 0; k < (2 * rows - comp); k++) {
			if ((k == 0) || (k == 2 * rows - comp - 1) || (i == 0) || (i == 2 * rows - 2)) {
				printf("%c ", i+65);
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}

	return 0;
}