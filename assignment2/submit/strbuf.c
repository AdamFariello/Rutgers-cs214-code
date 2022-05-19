#include <stdlib.h>
#include <stdio.h>
#include "strbuf.h"

#ifndef DEBUG
#define DEBUG 0
#endif

/*Create*/
int sb_init(strbuf_t *L, size_t length) {
    L->data = malloc(sizeof(char) * length);
    if (!L->data) 
	    return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void sb_destroy(strbuf_t *L) {
    free(L->data);
}

/*Queue*/
int sb_append(strbuf_t *L, char item) {
    /*Length can't start as zero, since 0 * # = 0*/
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

    L->data[L->used] = item;
    ++L->used;

    return 0;
}


int sb_remove(strbuf_t *L, char *item) {
    if (L->used == 0) 
	    return 1;

    --L->used;
    if (item) 
	    *item = L->data[L->used];
    return 1;
}

int sb_insert (strbuf_t *list, int index, char item) {
	//size increase
	if (list->used < index++) { 
		list->data = realloc(list, sizeof(int) * (index++));
		list->length = index;	
	}
	if (!list->data)
		return 1; 

	//search backwards
	for (int i = list->used + 1; i > index; i--) 
		list->data[i] = list->data[i - 1];
	list->data[index] = item;

	list->length++;
	list->used++;
	return 0;	
}

int sb_concat(strbuf_t *sb, char * str) {
	for(int i = 0; str[i] != '\0'; i++) 
		sb_append(sb, str[i]);
	return 0;
}
