#include <stdint.h>

#include "student.h"

typedef struct {
    //TODO use dynamic memory allocation like list
    Student** elements;
    int32_t length;
}Students;

Students* students_new();
void add(Students* students, Student* student);
int32_t index_of(Students* students, Student* student);
Student* get(Students* students, int8_t index);
void clear(Students* students);
void to_string_students(Students* students);
void sort();

