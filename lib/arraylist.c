#include <stdlib.h>
#include <assert.h>
#include "arraylist.h"

ArrayList *arraylist_create() {
    /* Allocate Memory */
    ArrayList *list = malloc(sizeof(ArrayList));
    assert(list != NULL);
    list->size = 0;
    list->data = calloc(2, sizeof(void *));
    assert(list->data != NULL);
    list->data[0] = NULL;
    return list;
}

void arraylist_setdata(ArrayList *list, void ** data, int max, int clear_data) {
    /* Sets the internal array of the arraylist */
    clear_data ? arraylist_clear(list) : NULL;
    list->data = data;
    list->size = max;
}

void arraylist_add(ArrayList *list, void *elem) {
    /* Adds one element of generic pointer type to the internal array */
    void ** new_data = realloc(list->data, arraylist_getsizeof(list));
    assert(new_data != NULL);
    new_data[list->size] = elem;
    arraylist_setdata(list, new_data, list->size + 1, 0);
}

void *arraylist_get(ArrayList *list, int index) {
    /* Gets an member of the array at an index */
    return list->data[index];
}

size_t arraylist_getsizeof(ArrayList *list) {
    /* Returns the size of the internal array in memory */
    return sizeof(*list->data);
}
size_t arraylist_getsize(ArrayList *list) {
    /* Returns the number of elements in the arraylist */
    return list->size;
}

void arraylist_remove(ArrayList *list, int index, int freeit) {
    /* Removes one element at and index */
    if (index > list->size - 1)
        return;
    if (list->size == 1) {
        arraylist_clear(list);
        return;
    }
    if (freeit)
        free(arraylist_get(list, index));
    for ( int i = index; i < list->size; ++i ) {
        if (i == list->size - 1)
            list->data[i] = NULL;
        else
            list->data[i] = list->data[i + 1];
    }
    void ** new_data = realloc(list->data, arraylist_getsizeof(list));
    --list->size;
    assert(new_data != NULL);
    arraylist_setdata(list, new_data, list->size, 0);
}

void arraylist_clear(ArrayList *list) {
    /* Clears the internal array */
    list->size = 0;
    free(list->data);
    list->data = NULL;
}

void arraylist_deallocate(ArrayList *list) {
    /* De-allocates the arraylist from memory
    No usage of the arraylist is allowed after this function call */
    if (list->data != NULL)
        free(list->data);
    free(list);
}

int arraylist_getindex(ArrayList *list, void *elem) {
    /* Looks for elem in list and returns the index or -1 if not found */
    for(int i = 0; i < list->size; ++i)
        if (elem == arraylist_get(list, i))
            return i;
    return -1;
}