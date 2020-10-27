#include <stdint.h>

#include "student.h"

typedef struct {
    Student elements[100];
    int8_t length;
}Students;

void add(Students* students, Student student);
int8_t index_of(Students students, Student student);
Student get(Students students, int8_t index);
void to_string_students(Students students);

