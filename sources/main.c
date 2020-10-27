#include <assert.h>
#include <stdio.h>

#include "student.h"

void test_program_seats(){
    set_program_seats(40, 50, 60);
    assert(get_total_seats_for_branch(BDA) == 40);
    assert(get_total_seats_for_branch(ML) == 40);
    assert(get_total_seats_for_branch(ES) == 60);
}

void test_register_new_student(){
    Student student1 = register_new_student("Sudheer", BDA, "sudheer@gmail.com");
    Student student2 = register_new_student("Rakshi", BDA, "rakshi@gmail.com");
    to_string(student1);
    to_string(student2);
}

int main(){
    // test_program_seats();
    test_register_new_student();
    return 0;
}

/*TODO
* Allocate a seat, generate reg #, handle different student statuses like allocated, withdrawn etc.

*/
