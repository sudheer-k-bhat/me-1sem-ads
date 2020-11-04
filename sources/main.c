/**
 * Console app to test the functionality
 * 
 * @author sudheer-k-bhat
 * @see admission_manager.h for available APIs.
 **/
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "models.h"
#include "admission_manager.h"
#include "log.h"
#include "arraylist.h"

//---------Test suite-----START---//
void test_program_seats(){
    log_info("[testcase]: test_program_seats()");
    set_program_seats(40, 50, 60);
    assert(get_total_seats_for_program(BDA) == 40);
    assert(get_total_seats_for_program(ML) == 50);
    assert(get_total_seats_for_program(ES) == 60);
}

void test_register_new_student(){
    log_info("[testcase]: test_register_new_student()");
    set_program_seats(40, 50, 60);
    StudentDTO* student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com", 5, 7.4);
    assert(student1->student->status == NEW && student1->error.code == 0);
}

void test_get_no_of_submitted_application(){
    log_info("[testcase]: test_get_no_of_submitted_application()");
    set_program_seats(40, 50, 60);
    int8_t num_of_students = 20;
    for (int8_t i = 0; i < num_of_students; i++)
    {
        char name[20];
        sprintf(name, "%dSudheer", i);
        char email[40];
        sprintf(email, "%dsudheer@gmail.com", i);
        StudentDTO* student1 = register_new_student(name, BDA, email, i+1, (7 + i*.1));
        assert(student1->student->status == NEW && student1->error.code == 0);
    }
    assert(get_number_of_submitted_applications() == num_of_students);
}

void bulk_register_students(PROGRAM_ID program_id, int8_t accept_student_size, int8_t reject_student_size){
    for (int8_t i = 0; i < accept_student_size; i++)
    {
        int8_t var = i + 10;
        char name[STUDENT_NAME_LEN];
        sprintf(name, "%dSudheer", i);
        char email[EMAIL_LEN];
        sprintf(email, "sudheer%d@gmail.com", i);
        StudentDTO* student1 = register_new_student(name, program_id, email, i+1, 7 + var*.01);
        assert(student1->student->status == NEW && student1->error.code == 0);
    }
    for (int8_t i = 0; i < reject_student_size; i++)
    {
        int8_t var = i + accept_student_size;
        char name[STUDENT_NAME_LEN];
        sprintf(name, "%dSudheer", i);
        char email[EMAIL_LEN];
        sprintf(email, "sudheer%d@gmail.com", i);
        StudentDTO* student1 = register_new_student(name, program_id, email, var + 1, 4 + var*.01);
        assert(student1->student->status == NEW && student1->error.code == 0);
    }
}

void test_allot_seats(){
    log_info("[testcase]: test_allot_seats()");
    set_program_seats(4, 5, 6);
    bulk_register_students(BDA, 6, 0);
    allot_seats();
    assert(get_filled_seats(BDA) == 4);
}

void test_allot_waitlist_seats(){
    log_info("[testcase]: test_allot_waitlist_seats()");
    set_program_seats(5, 5, 6);
    bulk_register_students(BDA, 7, 3);
    allot_seats();
    assert(get_filled_seats(BDA) == 5);
    PROGRAM_ID ids[] = {BDA, ML};
    provide_additional_program_options("sudheer5@gmail.com", ids);
    provide_additional_program_options("sudheer6@gmail.com", ids);
    increase_total_seats(BDA, 6);
    allot_seats_to_wating_list_students();
    assert(get_filled_seats(BDA) == 6);
    assert(get_filled_seats(ML) == 1);
}
//---------Test suite-----END---//

int main(){
    test_register_new_student();
    test_program_seats();
    test_get_no_of_submitted_application();
    test_allot_seats();
    test_allot_waitlist_seats();
    return 0;
}
