#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "student.h"
#include "log.h"

void test_program_seats(){
    log_info("[testcase]: test_program_seats()");
    set_program_seats(40, 50, 60);
    assert(get_total_seats_for_branch(BDA) == 40);
    assert(get_total_seats_for_branch(ML) == 50);
    assert(get_total_seats_for_branch(ES) == 60);
}

void test_register_new_students_generates_unique_regnums(){
    log_info("[testcase]: test_register_new_students_generates_unique_regnums()");
    set_program_seats(40, 50, 60);
    StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
    StudentDTO student2 = register_new_student("Rakshi", BDA, "rakshi@gmail.com");
    to_string_student_dto(student1);
    to_string_student_dto(student2);
    assert(strcmp(student1.student.regnum, student2.student.regnum) != 0);
}

void test_register_new_students_seats_full(){
    log_info("[testcase]: test_register_new_students_seats_full()");
    set_program_seats(1, 50, 60);
    StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
    StudentDTO student2 = register_new_student("Rakshi", BDA, "rakshi@gmail.com");
    to_string_student_dto(student1);
    to_string_student_dto(student2);
    assert(student2.error.code == ERROR_STUDENT_SEATS_FULL);
}

void test_register_same_student_twice(){
    log_info("[testcase]: test_register_same_student_twice()");
    set_program_seats(40, 50, 60);
    StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
    StudentDTO student2 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
    to_string_student_dto(student1);
    to_string_student_dto(student2);
    assert(student2.error.code == ERROR_STUDENT_ALREADY_EXISTS);
}

int main(){
    test_program_seats();
    test_register_new_students_generates_unique_regnums();
    test_register_new_students_seats_full();
    test_register_same_student_twice();
    return 0;
}

/*TODO
* Allocate a seat, generate reg #, handle different student statuses like allocated, withdrawn etc.

*/
