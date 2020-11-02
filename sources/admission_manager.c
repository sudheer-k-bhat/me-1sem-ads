#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "arraylist.h"
#include "admission_manager.h"

Programs programs = {
    {PROG_NAME_BD, 0, 0, "46", 1},
    {PROG_NAME_ML, 0, 0, "47", 1},
    {PROG_NAME_ES, 0, 0, "48", 1}};
ArrayList *students;

//-----private methods------//
void set_program_fields(Program *program, int8_t total_seats, int8_t filled_seats, int8_t reg_num_sequence)
{
    (*program).total_seats = total_seats;
    (*program).filled_seats = filled_seats;
    (*program).reg_num_sequence = reg_num_sequence;
}

Program *get_program(PROGRAM_ID id)
{
    switch (id)
    {
    case BDA:
        return &programs.bda;
    case ML:
        return &programs.ml;
    case ES:
        return &programs.es;
        //TODO
        // default:
        //     return NULL;
    }
}

/*
Year + Institution + Program + Roll #
20 + 10 + 46 + 015
*/
void generate_register_num(Program *program, char register_num[])
{
    char sequence[10], register_no[20];
    sprintf(sequence, "%03d", (*program).reg_num_sequence);
    strcpy(register_no, REG_NUM_YEAR_PART);
    strcat(register_no, REG_NUM_ORG_PART);
    strcat(register_no, (*program).code);
    strcat(register_no, sequence);
    strcpy(register_num, register_no);
    (*program).reg_num_sequence += 1;
}

//-----public methods------//
void set_program_seats(int8_t bda_total_seats, int8_t ml_total_seats, int8_t es_total_seats)
{
    set_program_fields(&programs.bda, bda_total_seats, 0, 1);
    set_program_fields(&programs.ml, ml_total_seats, 0, 1);
    set_program_fields(&programs.es, es_total_seats, 0, 1);
    //TODO
    students = arraylist_create();
}

int8_t get_total_seats_for_program(PROGRAM_ID program_id){
    return get_program(program_id)->total_seats;
}

void _to_string_students(ArrayList* students)
{
    log_debug("Students struct{length:%d, elements:[", arraylist_getsize(students));
    for (int8_t idx = 0; idx < arraylist_getsize(students); idx++)
    {
        student_to_string(arraylist_get(students, idx));
    }
    log_debug("]}");
}

StudentDTO* register_new_student(char name[], PROGRAM_ID program_id, char email[], int8_t entrance_test_rank,
float ug_grade)
{
    StudentDTO* model = (StudentDTO*)malloc(sizeof(StudentDTO));
    model->error.code = 0;
    model->error.message = "\0";
    model->student = NULL;
    // Student student = {"\0", "\0", 0, "\0", 0};

    // //TODO validate email
    // strcpy(student.email, email);
    int8_t index = -1; //arraylist_getindex(students, &student);

    //Student already registered
    if (index >= 0)
    {
        //TODO compare email
        // Student* student_ptr = (Student*) arraylist_get(students, index);
        // model.error.code = ERROR_STUDENT_ALREADY_EXISTS;
        // model.error.message = "Student has already registered";
        // model.student = *student_ptr;
    }
    else
    {
        Student* student = (Student*)malloc(sizeof(Student));
        strcpy(student->email, email); 
        strcpy(student->name, name);
        strcpy(student->regnum, "");
        student->program_id = program_id;
        student->status = NEW;
        student->entrance_test_rank = entrance_test_rank;
        student->ug_grade = ug_grade;
        student_to_string(student);
        //add student to list of registered students
        arraylist_add(students, student);
        model->student = student;
    }
    // _to_string_students(students);
    return model;
}

int8_t get_number_of_submitted_applications(){
    return arraylist_getsize(students);
}

int8_t get_filled_seats(PROGRAM_ID id){
    return get_program(id)->filled_seats;
}

void allot_seats(){
    assert(students != NULL && arraylist_getsize(students) > 0);
    //TODO for multiple programs
    // sort(&students);
    for(int32_t idx = 0; idx < arraylist_getsize(students); idx++){
        Student* student = arraylist_get(students, idx);
        Program* program = get_program(student->program_id);
        if(program->filled_seats < program->total_seats){
            char register_num[REG_NUM_LEN];
            generate_register_num(program, register_num);
            strcpy(student->regnum, register_num);
            student->status = ALLOTED;
            //increment filled seats
            (*program).filled_seats += 1;
        }else{
            student->status = REJECTED;
        }
    }
    _to_string_students(students);
    to_string_program(get_program(ES));
    to_string_program(get_program(BDA));
    to_string_program(get_program(ML));
}