#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "students.h"
#include "log.h"

Students* students_new(){
    Student elements[100];
    Students students = {(Student**)&elements, 0};
    return &students;
}

void add(Students *students, Student* student)
{
    students->elements[students->length] = student;
    students->length += 1;
}

int32_t index_of(Students* students, Student* student)
{
    for (int32_t idx = 0; idx < students->length; idx++)
    {
        if (strcmp(students->elements[idx]->email, student->email) == 0)
        {
            printf("%s %s %d", students->elements[idx]->email, student->email, idx);
            return idx;
        }
    }
    return -1;
}

Student* get(Students *students, int8_t index)
{
    //TODO handle invalid index
    return students->elements[index];
}

void to_string_students(Students* students)
{
    log_debug("Students struct{length:%d, elements:[", students->length);
    for (int8_t idx = 0; idx < students->length; idx++)
    {
        student_to_string(students->elements[idx]);
    }
    log_debug("]}");
}

//TODO
void clear(Students* students)
{
    for (int8_t i = 0; i < students->length; i++)
    {
        // students->elements[i] = NULL;
    }
    students->length = 0;
}

int cmpfunc(const void *a, const void *b)
{
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return (s1->entrance_test_rank - s2->entrance_test_rank);
}

void sort(Students *students)
{
    qsort(students->elements, students->length, sizeof(Student), cmpfunc);
}
