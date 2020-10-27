#include <stdint.h>
#include "app_constants.h"

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef enum _seat_status_ {
    ALLOTED,
    WAITING_LIST,
    WITHDRAWN,
    NEW
}SEAT_STATUS;

typedef enum _program_id_{
    BDA = 46,
    ML = 47,
    ES = 48
}PROGRAM_ID;

struct _student_ { //underscores to indicate internal representation
    char name[STUDENT_NAME_LEN];
    char regnum[REG_NUM_LEN];
    PROGRAM_ID program_id;
    char email[EMAIL_LEN];
    SEAT_STATUS status;
};
typedef struct _student_ Student;

struct _program_{
    char name[PROGRAM_NAME_LEN];
    int8_t total_seats;
    int8_t filled_seats;
    char code[PROGRAM_CODE_LEN];
    int8_t reg_num_sequence;
};
typedef struct _program_ Program;

struct _programs_ {
    Program bda;
    Program ml;
    Program es;
};
typedef struct _programs_ Programs;

void set_program_seats(int8_t bda, int8_t ml, int8_t es);
int8_t get_total_seats_for_branch(PROGRAM_ID);
void to_string(Student student);
void to_string_program(Program program);
//WIP
Student register_new_student(char name[], PROGRAM_ID, char email[]);
//TODO
int32_t get_admission_status(Student s1);
int8_t get_filled_seats(Program pg, char branch[]);

#endif