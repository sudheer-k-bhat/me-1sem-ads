#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "app_constants.h"
#include "student.h"
#include "students.h"
#include "log.h"

void to_string(Student student)
{
    log_debug("student struct{name:%s, regnum:%s, program_id:%d, email:%s, status:%d, entrance_test_rank:%d, ug_grade:%f}",
              student.name, student.regnum, student.program_id,
              student.email, student.status, student.entrance_test_rank, student.ug_grade);
}

void student_to_string(Student* student)
{
    log_debug("student struct{name:%s, regnum:%s, program_id:%d, email:%s, status:%d, entrance_test_rank:%d, ug_grade:%f}",
              student->name, student->regnum, student->program_id,
              student->email, student->status, student->entrance_test_rank, student->ug_grade);
}

void to_string_student_dto(StudentDTO* model)
{
    Student* student = model->student;
    log_debug("%d, %s", model->error.code, model->error.message);
    student_to_string(student);
}

void to_string_program(Program* program)
{
    log_debug("Program{code:%s, reg_num_sequence:%d, %d, %d}", program->code, program->reg_num_sequence,
    program->filled_seats, program->total_seats);
}