#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "app_constants.h"
#include "student.h"
#include "students.h"
#include "log.h"

Programs programs = {
    {PROG_NAME_BD, 0, 0, "46", 1},
    {PROG_NAME_ML, 0, 0, "47", 1},
    {PROG_NAME_ES, 0, 0, "48", 1}};
Students students;

void set_program_fields(Program *program, int8_t total_seats, int8_t filled_seats, int8_t reg_num_sequence){
    (*program).total_seats = total_seats;
    (*program).filled_seats = filled_seats;
    (*program).reg_num_sequence = reg_num_sequence;
}

void set_program_seats(int8_t bda, int8_t ml, int8_t es)
{
    set_program_fields(&programs.bda, bda, 0, 1);
    set_program_fields(&programs.ml, ml, 0, 1);
    set_program_fields(&programs.es, es, 0, 1);
    students.length = 0;
}

//refactor
int8_t get_total_seats_for_branch(PROGRAM_ID id)
{
    switch (id)
    {
    case BDA:
        return programs.bda.total_seats;
    case ML:
        return programs.ml.total_seats;
    case ES:
        return programs.es.total_seats;
    default:
        return -1;
    }
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

StudentDTO register_new_student(char name[],
                             PROGRAM_ID id, char email[])
{
    StudentDTO model;
    model.error.code = 0;
    model.error.message = "\0";
    Student student = {"\0", "\0", 0, "\0", 0};

    strcpy(student.email, email);
    int8_t index = index_of(students, student);

    //Student already registered
    if (index >= 0)
    {
        student = get(students, index);
        model.error.code = ERROR_STUDENT_ALREADY_EXISTS;
        model.error.message = "Student has already registered";
        model.student = student;
    }
    else
    {
        Program *program = get_program(id);
        //Seats available
        if ((*program).filled_seats < (*program).total_seats)
        {
            char register_num[REG_NUM_LEN];
            generate_register_num(program, register_num);
            strcpy(student.name, name);
            strcpy(student.regnum, register_num);
            student.program_id = id;
            student.status = ALLOTED;
            //add student to list of registered students
            add(&students, student);
            //increment filled seats
            (*program).filled_seats += 1;
            model.student = student;
        }else{
            model.error.code = ERROR_STUDENT_SEATS_FULL;
            model.error.message = "No seats available under this program";
            model.student = student;
        }
    }
    //TODO handle other cases and also maintain state
    return model;
}

void to_string(Student student)
{
    log_debug("student struct{name:%s, regnum:%s, program_id:%d, email:%s, status:%d}",
              student.name, student.regnum, student.program_id,
              student.email, student.status);
}

void to_string_student_dto(StudentDTO model)
{
    Student student = model.student;
    log_debug("studentdto struct{student: {name:%s, regnum:%s, program_id:%d, email:%s, status:%d}, error: {code:%d, message:%s}}",
              student.name,
              student.regnum,
              student.program_id,
              student.email,
              student.status,
              model.error.code,
              model.error.message);
}

void to_string_program(Program program)
{
    log_debug("Program{code:%s, reg_num_sequence:%d}", program.code, program.reg_num_sequence);
}