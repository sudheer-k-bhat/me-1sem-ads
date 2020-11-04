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
void _set_program_fields(Program *program, int8_t total_seats, int8_t filled_seats, int8_t reg_num_sequence)
{
    (*program).total_seats = total_seats;
    (*program).filled_seats = filled_seats;
    (*program).reg_num_sequence = reg_num_sequence;
}

Program* _get_program(PROGRAM_ID id)
{
    switch (id)
    {
    case BDA:
        return &programs.bda;
    case ML:
        return &programs.ml;
    case ES:
        return &programs.es;
    }
}

/*
Year + Institution + Program + Roll #
20 + 10 + 46 + 015
*/
void _generate_register_num(Program *program, char register_num[])
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

void _to_string_students(ArrayList *students)
{
    log_debug("Students struct{length:%d, elements:[", arraylist_getsize(students));
    for (int8_t idx = 0; idx < arraylist_getsize(students); idx++)
    {
        student_to_string(arraylist_get(students, idx));
    }
    log_debug("]}");
}

void _allot_seat(Program *program, Student *student){
    char register_num[REG_NUM_LEN];
    _generate_register_num(program, register_num);
    strcpy(student->regnum, register_num);
    student->status = ALLOTED;
    //increment filled seats
    program->filled_seats += 1;
}

int cmpfunc(const void *a, const void *b)
{
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return (s1->entrance_test_rank - s2->entrance_test_rank);
}

void sort()
{
    qsort(students->data, arraylist_getsize(students), sizeof(Student*), cmpfunc);
}

//-----public methods------//
void set_program_seats(int8_t bda_total_seats, int8_t ml_total_seats, int8_t es_total_seats)
{
    _set_program_fields(&programs.bda, bda_total_seats, 0, 1);
    _set_program_fields(&programs.ml, ml_total_seats, 0, 1);
    _set_program_fields(&programs.es, es_total_seats, 0, 1);
    students = arraylist_create();
}

int8_t get_total_seats_for_program(PROGRAM_ID program_id)
{
    return _get_program(program_id)->total_seats;
}

StudentDTO *register_new_student(char name[], PROGRAM_ID program_id, char email[], int8_t entrance_test_rank,
                                 float ug_grade)
{
    StudentDTO *model = (StudentDTO *)malloc(sizeof(StudentDTO));
    model->error.code = 0;
    model->error.message = "\0";
    model->student = NULL;
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->email, email);
    strcpy(student->name, name);
    strcpy(student->regnum, "");
    student->program_id = program_id;
    student->status = NEW;
    student->entrance_test_rank = entrance_test_rank;
    student->ug_grade = ug_grade;
    //add student to list of registered students
    arraylist_add(students, student);
    model->student = student;
    return model;
}

int8_t get_number_of_submitted_applications()
{
    return arraylist_getsize(students);
}

int8_t get_filled_seats(PROGRAM_ID id)
{
    return _get_program(id)->filled_seats;
}

void allot_seats()
{
    assert(students != NULL && arraylist_getsize(students) > 0);
    for (int32_t idx = 0; idx < arraylist_getsize(students); idx++)
    {
        Student *student = arraylist_get(students, idx);
        Program *program = _get_program(student->program_id);
        if (student->status == NEW)
        {
            if (student->ug_grade < 5.0)
            {
                student->status = REJECTED;
            }
            else
            {
                if (program->filled_seats < program->total_seats)
                {
                    _allot_seat(program, student);
                }
                else
                {
                    student->status = WAITING_LIST;
                }
            }
        }
    }
}

void provide_additional_program_options(char student_email[], PROGRAM_ID ids[])
{
    assert(students != NULL && arraylist_getsize(students) > 0);
    for (int32_t idx = 0; idx < arraylist_getsize(students); idx++)
    {
        Student *student = arraylist_get(students, idx);
        if (strcmp(student->email, student_email) == 0)
        {
            student->additional_program_ids[0] = ids[0];
            student->additional_program_ids[1] = ids[1];
        }
    }
}

void increase_total_seats(PROGRAM_ID program_id, int8_t seats)
{
    Program *program = _get_program(program_id);
    assert(seats > program->total_seats);
    program->total_seats = seats;
}

void allot_seats_to_wating_list_students()
{
    assert(students != NULL && arraylist_getsize(students) > 0);
    for (int32_t idx = 0; idx < arraylist_getsize(students); idx++)
    {
        Student *student = arraylist_get(students, idx);
        if (student->status == WAITING_LIST)
        {
            uint8_t alloted = 0;
            for(int8_t prog_idx = 0; prog_idx < 2; prog_idx++){
                Program *program = _get_program(student->additional_program_ids[prog_idx]);
                if (program->filled_seats < program->total_seats)
                {
                    _allot_seat(program, student);
                    alloted = 1;
                    break;
                }
            }
            if(alloted == 0){
                student->status = REJECTED;
            }
        }
    }
}