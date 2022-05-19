#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

#ifndef DEBUG
#define DEBUG 0
#endif

/*Create*/
int al_init(arraylist_t *L, size_t length) {
    L->data = malloc(sizeof(int) * length);
    if (!L->data) 
	    return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void al_destroy(arraylist_t *L) {
    free(L->data);
}

/*Queue*/
int al_append(arraylist_t *L, int item) {
    /*Length can't start as zero, since 0 * # = 0*/
    if (L->used == L->length) {
	size_t size = L->length * 2;
	int *p = realloc(L->data, sizeof(int) * size);
	if (!p) 
		return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) 
		printf("Increased size to %lu\n", size);
    }
    ++L->used;

    return 0;
}


int al_remove(arraylist_t *L, int *item) {
    if (L->used == 0) 
	    return 1;

    --L->used;
    if (item) 
	    *item = L->data[L->used];
    return 1;
}

int al_insert (arraylist_t *list, int index, int item) {
	//size increase
	if (list->used < index + 1) { 
		list->data = realloc(list->data, sizeof(int) * (index + 1));
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
