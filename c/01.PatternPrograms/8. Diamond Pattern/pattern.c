# include <stdio.h>

/*

*/

int main()
{
	printf("8. Diamond Pattern \n");
	printf("------------------ \n");

	int rows = 5;
	for (int i = 0; i < 2*rows -1; i++) {
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
			printf("* ");
		}
		printf("\n");
	}

	printf("------------------ \n");

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
			printf("%i ", i+1);
		}
		printf("\n");
	}

	printf("------------------ \n");

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
			printf("%c ", 65+i);
		}
		printf("\n");
	}

	return 0;
}