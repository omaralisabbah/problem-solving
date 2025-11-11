# include <stdio.h>

/*
	Hourglass Pattern is a combination of the inverted full pyramid and full
	pyramid patterns but in the opposite sense to that of diamond pattern. Here we join them using their tip.

*/

int main()
{
	printf("9. Hourglass Pattern \n");
	printf("-------------------- \n");

	int rows = 5;
	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) -1;
		}
		else {
			comp = 2 * (i - rows + 1) +1;
		}
		for (int j = 0; j < (2 * rows - comp - 1); j++) {
			printf(" ");
		}
		for (int k = 0; k < comp; k++) {
			printf("* ");
		}
		printf("\n");
	}
	

	printf("-------------------- \n");

	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) - 1;
		}
		else {
			comp = 2 * (i - rows + 1) + 1;
		}
		for (int j = 0; j < (2 * rows - comp - 1); j++) {
			printf(" ");
		}
		for (int k = 0; k < comp; k++) {
			printf("%i ", i+1);
		}
		printf("\n");
	}

	printf("-------------------- \n");

	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) - 1;
		}
		else {
			comp = 2 * (i - rows + 1) + 1;
		}
		for (int j = 0; j < (2 * rows - comp - 1); j++) {
			printf(" ");
		}
		for (int k = 0; k < comp; k++) {
			printf("%c ", i+65);
		}
		printf("\n");
	}

	return 0;
}


/*
	int rows = 5;
	for (int i = 0; i < (2 * rows - 1); i++) {
		int comp;
		if (i < rows) {
			comp = 2 * (rows - i) -1;
		}
		else {
			comp = 2 * (i - rows + 1) +1;
		}
		for (int j = 0; j < comp; j++) {
			printf(" ");
		}
		for (int k = 0; k < 2*rows - 1; k++) {
			printf("* ");
		}
		printf("\n");
	}
*/