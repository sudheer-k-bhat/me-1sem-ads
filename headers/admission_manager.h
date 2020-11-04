/**
 * API for managing student admission activities.
 * 
 * @author sudheer-k-bhat
 * @see models.h for models used.
 **/
#include <stdint.h>

#include "models.h"
#ifndef ADMISSION_MANAGER_H_INCLUDED
#define ADMISSION_MANAGER_H_INCLUDED

/**
 * Register a student in the admission process.
 * @role student
 **/
StudentDTO* register_new_student(char name[], PROGRAM_ID program_id, char email[], int8_t entrance_test_rank,
float ug_grade);

/**API to store program isn't provided. However, 3 default programs and APIs
 * to edit them are provided
*/
//void store_program(Program program);

/**
 * Set total seats for each program.
 * @role admin
 **/
void set_program_seats(int8_t bda_total_seats, int8_t ml_total_seats, int8_t es_total_seats);

/**
 * Get total seats for each program.
 * @role admin
 **/
int8_t get_total_seats_for_program(PROGRAM_ID program_id);

/**
 * Allot seats to registered students.
 * @description Students with CGPA < 5 will be rejected. If seats are filled up, student
 * will be put on waiting list.
 * @role admin
 **/
void allot_seats();

/**
 * Get number of submitted applications.
 * @role admin
 **/
int8_t get_number_of_submitted_applications();

/**
 * Get number of filled seats for given program.
 * @role admin
 **/
int8_t get_filled_seats(PROGRAM_ID id);

/**
 * Provide additional program options for use in alloting if in wait list.
 * @role student
 * @param Provide 2 program options.
 **/
void provide_additional_program_options(char student_email[], PROGRAM_ID ids[]);

/**
 * Increase total seats for given program to make room for some wait list students.
 * @role admin
 **/
void increase_total_seats(PROGRAM_ID program_id, int8_t seats);

/**
 * Allot seats to waitlisting students.
 * @description Each student in the waiting list will be tried to allot seats in
 * one of the program options (in the order of student preference). If seats are filled in both
 * options, student will be rejected.
 * @role admin
 **/
void allot_seats_to_wating_list_students();

#endif









