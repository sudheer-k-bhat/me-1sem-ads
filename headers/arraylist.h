/**
 * A general purpose arraylist (similar to list in C++)
 * 
 * @author Credits: https://codereview.stackexchange.com/questions/64423/implementing-an-arraylist
 **/
#include <stdint.h>

#ifndef ARRAY_LIST_H_INCLUDED
#define ARRAY_LIST_H_INCLUDED

typedef struct {
    size_t size;
    void ** data;
} ArrayList;

ArrayList *arraylist_create();

void arraylist_setdata(ArrayList *list, void ** data, int max, int clear_data);

void arraylist_add(ArrayList *list, void *elem);

void *arraylist_get(ArrayList *list, int index);

size_t arraylist_getsizeof(ArrayList *list);
size_t arraylist_getsize(ArrayList *list);

void arraylist_remove(ArrayList *list, int index, int freeit);

void arraylist_clear(ArrayList *list);

void arraylist_deallocate(ArrayList *list);

int arraylist_getindex(ArrayList *list, void *elem);

#endif