#include <stdint.h>
#include "app_constants.h"

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

typedef enum {
    ALLOTED = 10,
    WAITING_LIST,
    WITHDRAWN,
    NEW
}SEAT_STATUS;

typedef enum {
    BDA = 46,
    ML = 47,
    ES = 48
}PROGRAM_ID;

typedef enum {
    ERROR_STUDENT_ALREADY_EXISTS = 10,
    ERROR_STUDENT_SEATS_FULL = 20
}ERROR_CODES;

typedef struct {
    char name[STUDENT_NAME_LEN];
    char regnum[REG_NUM_LEN];
    PROGRAM_ID program_id;
    char email[EMAIL_LEN];
    SEAT_STATUS status;
} Student;

typedef struct {
    char name[PROGRAM_NAME_LEN];
    int8_t total_seats;
    int8_t filled_seats;
    char code[PROGRAM_CODE_LEN];
    //TODO change to 32
    int8_t reg_num_sequence;
} Program;

typedef struct {
    Program bda;
    Program ml;
    Program es;
} Programs;

typedef struct {
    int8_t code;
    char* message;
} Error;

typedef struct {
    Student student;
    Error error;
} StudentDTO;

void set_program_seats(int8_t bda, int8_t ml, int8_t es);
int8_t get_total_seats_for_branch(PROGRAM_ID);
void to_string(Student student);
void to_string_program(Program program);
void to_string_student_dto(StudentDTO model);
//WIP
StudentDTO register_new_student(char name[], PROGRAM_ID, char email[]);
//TODO
int32_t get_admission_status(Student s1);
int8_t get_filled_seats(Program pg, char branch[]);

#endif