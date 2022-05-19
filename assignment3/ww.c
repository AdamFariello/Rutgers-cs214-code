#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* THIS ISN't THE REAL WW*/
int main (int argc, char ** argv) {
	if (strcmp(argv[2], "ERROR" ) == 0)
		return EXIT_FAILURE;
	else if (strcmp (argv[2], "Empty") == 0) {
		printf("\n\n\n\n\n\n");
		return EXIT_SUCCESS;
	}
	else if (strcmp (argv[2], "Empty") != 0)
		printf("Fake WW called with %s %s\n", argv[1], argv[2]);
	return EXIT_SUCCESS;
}
