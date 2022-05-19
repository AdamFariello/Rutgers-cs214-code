/* Adam Fariello
 * Due: February 11
 * assignment: 1
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void triangle(unsigned width)
{
    unsigned i, j;
    
    i = 0;
    while (i <= width) {
        j = 0;
        while (j < i) {
            putchar('*');
            ++j;
        }
        putchar('\n');
        ++i;
    }
}

void triangle2 (int a) {
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < i + 1; j++)
			printf("*");
		printf("\n");
	}
}

void v_triangle(int a) {
	printf("Lines: %d\n", a);
	for (int i = a; i > 0; i--) {
		for (int j = 0; j < i; j++)
			printf("*");
		printf("\n");
	}
}

void h_triangle(int a) {
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < i; j++)
		       printf(" ");	
		for (int j = 0; j < a - i; j++)
			printf("*");
		printf("\n");
	}
}

int main (int argc, char * argv[argc+1]) {
	int w = 5;

	if (argc < 2)
		triangle(w);
	else {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "triangle") == 0)
				triangle(w);
			else if (strcmp(argv[i], "triangle2") == 0)
				triangle2(w);
			else if (strcmp(argv[i], "triangleV") == 0)
				v_triangle(w);
			else if (strcmp(argv[i], "triangleH") == 0)
				h_triangle(w);
			else 
				return EXIT_FAILURE;
			printf("\n");
		}
	}
	return EXIT_SUCCESS;
}
