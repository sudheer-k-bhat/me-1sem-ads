#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "app_constants.h"
#include "student.h"


Programs programs = {
    {PROG_NAME_BD, 0, 0, "46", 1},
    {PROG_NAME_ML, 0, 0, "47", 1},
    {PROG_NAME_ES, 0, 0, "48", 1}
};

void set_program_seats(int8_t bda, int8_t ml, int8_t es){
    programs.bda.total_seats = bda;
    programs.ml.total_seats = ml;
    programs.es.total_seats = es;
}

//refactor
int8_t get_total_seats_for_branch(PROGRAM_ID id){
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

Program* get_program(PROGRAM_ID id){
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
void generate_register_num(PROGRAM_ID id, char register_num[]){
    Program* program = get_program(id);
    char sequence[10], register_no[20];
    sprintf(sequence, "%03d", (*program).reg_num_sequence);
    strcpy(register_no, REG_NUM_YEAR_PART);
    strcat(register_no, REG_NUM_ORG_PART);
    strcat(register_no, (*program).code);
    strcat(register_no, sequence);
    strcpy(register_num, register_no);
    // printf("%s, %s", register_num, register_no);
    (*program).reg_num_sequence += 1;
    // printf("%d", (*program).reg_num_sequence);
}

Student register_new_student(char name[],
    PROGRAM_ID id, char email[]){
    char register_num[REG_NUM_LEN];
    generate_register_num(id, register_num);
    Student student;
    strcpy(student.name, name);
    strcpy(student.regnum, register_num);
    student.program_id = id;
    strcpy(student.email, email);
    student.status = ALLOTED;
    // to_string(student);
    //TODO handle other cases and also maintain state
    return student;
}

void to_string(Student student){
    printf("\nstudent struct{name:%s, regnum:%s, program_id:%d, email:%s, status:%d}\n",
        student.name, student.regnum, student.program_id,
        student.email, student.status);
}

void to_string_program(Program program){
    printf("\nProgram{code:%s, reg_num_sequence:%d}\n", program.code, program.reg_num_sequence);
}