#include "models.h"
#include "log.h"

void student_to_string(Student* student)
{
    log_debug("student struct{name:%s, regnum:%s, program_id:%d, email:%s, status:%d, entrance_test_rank:%d, ug_grade:%f}",
              student->name, student->regnum, student->program_id,
              student->email, student->status, student->entrance_test_rank, student->ug_grade);
}