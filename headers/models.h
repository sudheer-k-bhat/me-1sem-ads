/**
 * Data structures used.
 * 
 * @author sudheer-k-bhat
 * @see admission_manager.h for how the models are used in the API.
 **/
#include <stdint.h>
#include "app_constants.h"

#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED

typedef enum {
    ALLOTED = 10,
    WAITING_LIST = 20,
    NEW = 40,
    REJECTED = 50
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
    int8_t entrance_test_rank;
    float ug_grade;
    PROGRAM_ID additional_program_ids[2];
} Student;

typedef struct {
    char name[PROGRAM_NAME_LEN];
    int8_t total_seats;
    int8_t filled_seats;
    char code[PROGRAM_CODE_LEN];
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
    Student* student;
    Error error;
} StudentDTO;

void student_to_string(Student* student);

#endif