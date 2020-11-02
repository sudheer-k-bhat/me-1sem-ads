#include <stdint.h>

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