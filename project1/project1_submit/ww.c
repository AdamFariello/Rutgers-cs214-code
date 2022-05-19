#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#ifndef DEBUG
#define DEBUG 0
#endif


/*strbuf stuf*/
typedef struct {
    size_t length;
    size_t used;
    char *data;
} strbuf_t;


/*strbuf methods*/
int sb_init(strbuf_t *L, size_t length)
{
    L->data = malloc(sizeof(char) * length);
    if (!L->data) return 1;
	L->data[0]='\0';
    L->length = length;
    L->used   = 1;

    return 0;
}

void sb_destroy(strbuf_t *L){
    free(L->data);
}

int sb_append(strbuf_t *L, char item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	char *p = realloc(L->data, sizeof(char) * size);
	if (!p) 
		return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) 
		printf("Increased size to %lu\n", size);
    }

    L->data[L->used-1] = item;
    L->data[L->used] = '\0';
    ++L->used;

    return 0;
}

char sb_get(strbuf_t *list, int i){
	return list->data[i];
}


int sb_concat(strbuf_t *sb, char *str)
{
	while((sb->used+strlen(str))>sb->length){
		size_t size= sb->length*2;
		char *p=realloc(sb->data, sizeof(char)*size);
		if (!p) return 1;
		sb->data=p;
		sb->length=size;
	}
	for(int i=0; i<strlen(str); ++i){
		sb_append(sb, str[i]);
	} 
	
	return 0;
}


/*reguarlar methods*/
int isdir(char* name){
	//check if directory, copied from lecture
	struct stat data;
	int err = stat(name, &data);
	if (err) {
		perror(name);
		return 0;
	}
	if (S_ISDIR(data.st_mode)) 
		return 1;
	
	return 0;
}

int isreg(char* name){
	//check if regular file, copied from lecture
	struct stat data;
	int err=stat(name, &data);
	if (err){
		perror(name);
		return 0;
	}
	if (S_ISREG(data.st_mode)) return 1;
	
	return 0;
}

int nameCheck(char* name){
	//check if file name is appropriate
	if (strncmp(name, "wrap",strlen("wrap"))==0) 
		return 0;
	if (name[0]=='.') 
		return 0;
	
	return 1;
}

char ptr;

//line counter so that only make up one '/n'
int line;
int readAndwrite(int fr, strbuf_t *buff){
	//ptr is declated outside so it can
	//plus 1 to go over spaces
	int wordcount = 0;

	//&& condition stops word "mutation"
	do {
		if (read(fr, &ptr, 1) == 0)
			break;
		
		wordcount++;
		sb_append(buff, ptr);
	}	while (isspace(ptr) == 0);
	
	//mark a prev line change
	if (wordcount==1 && buff->data[0]=='\n'){
		line++;
	} 

	//deletes whitespace from +2 letter words
	if (wordcount > 1)
		for (int i = 0; i < wordcount; i++) 
			if  (isspace(buff->data[i]) != 0){
				if (buff->data[i]=='\n'){
					line++;
				}
				else{
					line=0;
				}
				buff->data[i] = ' ';
			}
	ptr++;
	return wordcount;
}

int wrapcount(int wrap, int count, int word) {
	//count if need to change line
	//return 1 if need, 0 if no need
	if ((count + word) > wrap) 
		return 1;
	else 
		return 0;
}

void printFile(char* fileW){
	//prints the content of fileW
	char ptr;
	int file=open(fileW, O_RDONLY);
	while(file){
		if (read(file, &ptr,1)==0) break;
		printf("%c", ptr);
	}
	close(file);
}

char* fileWriter(int status, int wrap, char* fileR, char* fileW){
	//wrap fileR to wrap.fileR
	//returns wrap.fileR
	
	int mode=1;
	int fw;

	if (strstr(fileW, "None") == NULL)){
		fw = open (fileW, O_WRONLY|O_TRUNC|O_CREAT, 0777);
		mode=2;
	}else{
		fw=0;
	}
		
	int count = 0;
	int fp = open(fileR, O_RDONLY);
		while (fp) {		
			strbuf_t buff;
			sb_init(&buff,1);
			
			int c = readAndwrite(fp, &buff);
			
			//word too long
			if (c - 1 > wrap)
				status = 1;

			//Stops bad white space 
			if (c > 1 || (c == 1 && buff.data[0] == '\n' && line>1)) {
				
				//reset count if there is an orginal line change from text
				if (c == 1 && buff.data[0] == '\n'){
					//make up line change for blank lines
					if (line==2){
						if (mode==2) write(fw, "\n", 1);
						else printf("\n");
					}
					count=0;
				}
				
				//sentence too long
				//line change because of wrapping
				if (wrapcount(wrap, count, c - 1) == 1) {
					if (mode==2) write(fw, "\n", 1);
					else printf("\n");
					count = 0;
				}
				
				count += c;
				if (mode==2) write(fw, buff.data, buff.used-1);
				else printf("%s",buff.data);
			}
			sb_destroy(&buff);	
		
			if (c == 0)
				break;
		}
		if (mode==2) write(fw, "\n", 1);
		else printf("\n");
	close(fp);
	if (mode==2) close(fw);
	return fileW;
}


int main (int argc, char * argv[argc + 1]) {
	//1 = width & 2 = file
	if (argc != 3) 
		return EXIT_FAILURE;
		
	int wrap = atoi(argv[1]);
	int status = 0;
	char* input=argv[2];
	
	
	//if input is regular file, check its name
	//write into a file then print the file
	//delet the written file <-failed
	if ((isreg(input)==1)&&(nameCheck(input)==1)){
		fileWriter(status, wrap, input, "None");
	}else if (isdir(input)==1){
		DIR *d;
		struct dirent *dir;
		d=opendir(input);
		chdir(input);
		if (d){
			while((dir=readdir(d))!=NULL){
				//printf("%s\n", dir->d_name);
				char* fileR=dir->d_name;
				if (nameCheck(fileR)==1){
					//make a new name for the file to write in
					strbuf_t b;
					sb_init(&b,1);
					sb_concat(&b,"wrap.");
					sb_concat(&b,fileR);
					char* fileW=b.data;
					fileWriter(status, wrap, fileR, fileW);
					sb_destroy(&b); 
				}
			}
			closedir(d);
		}
	}else status = 1;

	if (status == 1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
