#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "student.h"
#include "admission_manager.h"
#include "log.h"
#include "arraylist.h"

void test_program_seats(){
    log_info("[testcase]: test_program_seats()");
    set_program_seats(40, 50, 60);
    assert(get_total_seats_for_program(BDA) == 40);
    assert(get_total_seats_for_program(ML) == 50);
    assert(get_total_seats_for_program(ES) == 60);
}

// void test_register_new_student(){
//     log_info("[testcase]: test_register_new_student()");
//     set_program_seats(40, 50, 60);
//     StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com", 5, 7.4);
//     assert(student1.student->status == NEW && student1.error.code == 0);
// }

// void test_get_no_of_submitted_application(){
//     log_info("[testcase]: test_get_no_of_submitted_application()");
//     set_program_seats(40, 50, 60);
//     int8_t num_of_students = 20;
//     for (int8_t i = 0; i < num_of_students; i++)
//     {
//         char name[20];
//         sprintf(name, "%dSudheer", i);
//         char email[40];
//         sprintf(email, "%dsudheer@gmail.com", i);
//         StudentDTO student1 = register_new_student(name, BDA, email, i+1, (7 + i*.1));
//         assert(student1.student->status == NEW && student1.error.code == 0);
//         to_string_student_dto(student1);
//     }
//     assert(get_number_of_submitted_applications() == num_of_students);
// }

void test_registered_students_sorting_helper(PROGRAM_ID program_id){
    int8_t num_of_students = 10;
    int8_t var2 = program_id == BDA ? 10 : (program_id == ML ? 20 : 30);
    for (int8_t i = 0; i < num_of_students; i++)
    {
        int8_t var = i+10;
        char name[20];
        sprintf(name, "%dSudheer", i);
        char email[40];
        sprintf(email, "sudheer%d@gmail.com", i);
        StudentDTO* student1 = register_new_student(name, program_id, email, i+1, 7 + var*.01);
        assert(student1->student->status == NEW && student1->error.code == 0);
    }
}

// void test_registered_students_sorting(){
//     log_info("[testcase]: test_registered_students_sorting()");
//     set_program_seats(40, 50, 60);
//     test_registered_students_sorting_helper(ES);
//     // test_registered_students_sorting_helper(BDA);
//     // test_registered_students_sorting_helper(ML);
//     allot_seats();
// }

// void test_register_new_students_generates_unique_regnums(){
//     log_info("[testcase]: test_register_new_students_generates_unique_regnums()");
//     set_program_seats(40, 50, 60);
//     StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
//     StudentDTO student2 = register_new_student("Rakshi", BDA, "rakshi@gmail.com");
//     to_string_student_dto(student1);
//     to_string_student_dto(student2);
//     assert(strcmp(student1.student.regnum, student2.student.regnum) != 0);
// }

// void test_register_new_students_seats_full(){
//     log_info("[testcase]: test_register_new_students_seats_full()");
//     set_program_seats(1, 50, 60);
//     StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
//     StudentDTO student2 = register_new_student("Rakshi", BDA, "rakshi@gmail.com");
//     to_string_student_dto(student1);
//     to_string_student_dto(student2);
//     assert(student2.error.code == ERROR_STUDENT_SEATS_FULL);
// }

// void test_register_same_student_twice(){
//     log_info("[testcase]: test_register_same_student_twice()");
//     set_program_seats(40, 50, 60);
//     StudentDTO student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
//     StudentDTO student2 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
//     to_string_student_dto(student1);
//     to_string_student_dto(student2);
//     assert(student2.error.code == ERROR_STUDENT_ALREADY_EXISTS);
// }

//----


void test_allot_seats(){
    log_info("[testcase]: test_allot_seats()");
    set_program_seats(40, 50, 60);
    test_registered_students_sorting_helper(ES);
    // to_string_student_dto(student1);
    allot_seats();
}

int main(){
    // test_program_seats();
    // test_register_new_student();
    // test_get_no_of_submitted_application();

    // test_registered_students_sorting();
    // test_register_new_students_generates_unique_regnums();
    // test_register_new_students_seats_full();
    // test_register_same_student_twice();

    // test_arraylist();

    test_allot_seats();

    return 0;
}

/*TODO
* Allocate a seat, generate reg #, handle different student statuses like allocated, withdrawn etc.

*/
