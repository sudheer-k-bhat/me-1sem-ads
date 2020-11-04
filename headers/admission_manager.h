#include <stdint.h>

#include "models.h"
#ifndef ADMISSION_MANAGER_H_INCLUDED
#define ADMISSION_MANAGER_H_INCLUDED

StudentDTO* register_new_student(char name[], PROGRAM_ID program_id, char email[], int8_t entrance_test_rank,
float ug_grade);

/**API to store program isn't provided to considering
 * assignment timeframe. However, 3 default programs and APIs
 * to edit them are provided
*/
//void store_program(Program program);

void set_program_seats(int8_t bda_total_seats, int8_t ml_total_seats, int8_t es_total_seats);

int8_t get_total_seats_for_program(PROGRAM_ID program_id);

void allot_seats();

int8_t get_number_of_submitted_applications();

int8_t get_filled_seats(PROGRAM_ID id);

void provide_additional_program_options(char student_email[], PROGRAM_ID ids[]);

void increase_total_seats(PROGRAM_ID program_id, int8_t seats);

void allot_seats_to_wating_list_students();

#endif









