#include <string.h>
#include <stdio.h>

#include "student.h"
#include "students.h"
#include "log.h"

void add(Students* students, Student student){
    (*students).elements[(*students).length] = student;
    (*students).length += 1;
    to_string_students((*students));
}

int8_t index_of(Students students, Student student){
    log_debug("%d %s", students.length, student.email);
    for(int8_t idx = 0; idx < students.length; idx++){
        // printf("%s %s", students.elements[idx].email, student.email);
        if(strcmp(students.elements[idx].email, student.email) == 0){
            return idx;
        }
    }
    return -1;
}

Student get(Students students, int8_t index){
    //TODO handle invalid index
    return students.elements[index];
}

void to_string_students(Students students){
    log_debug("Students struct{length:%d, elements:}", students.length);
}