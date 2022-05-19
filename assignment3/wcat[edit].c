#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#ifndef WWPATH
#define WWPATH "./ww"
#endif

int isdirectory(char* name){
	//check if directory, copied from lecture
	struct stat data;
	stat(name, &data);
	if (S_ISDIR(data.st_mode)) {
		printf("%s is a directory\n", name);
		return 1;
	}

	return 0;
}

int main (int argc, char * argv [argc+1]) {
	if (argc < 2) 
		return EXIT_FAILURE;
	
	//argv[0] = command 
	//argv[1] = line width
	int programSuccess = EXIT_SUCCESS;
	for (int i = 2; i < argc; i++) {
		if (isdirectory(argv[i]) == 0){
			int fd[2];
			pipe(fd);
			pid_t child = fork();
	
			if (child == -1) { 
				perror("Fork Fail");
				abort();
			}

			if (child == 0) {
				close(fd[0]);
				dup2(fd[1], 1);
			        execl(WWPATH, WWPATH, argv[1], argv[i], NULL);
			
				close(fd[1]);
			} else {
				//int intfd, outfd;
				//int bytes; 
				char buf[SHRT_MAX];

				//while ((bytes = read(fd[0] , buf, 28)) > 0)
				//	write(fd[1], buf, bytes);
				
				read(fd[0] , buf, SHRT_MAX); 
				printf("%s", buf);

				//bytes = read(fd[0] , buf, 100); 	
				//write(fd[1], buf, bytes);
				close(fd[0]);
			}

			wait(NULL);	
		}
		else  
			programSuccess = EXIT_FAILURE;
	}
	return programSuccess;	
}
