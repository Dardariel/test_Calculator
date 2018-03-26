#ifndef __LIB_MY_MATH__
#define __LIB_MY_MATH__

/* TypeWork - Тип операции (+,-,/,*)
 * OperandA и OperandB
 * ErrorCode
 */

#define LMM_OPERATION_PLUS 1
#define LMM_OPERATION_MINUS 2
#define LMM_OPERATION_MULTIPLY 3
#define LMM_OPERATION_DIVIDE 4

#define LMM_NO_ERROR 0
#define LMM_ERROR_DIVISION_BY_ZERO 1
#define LMM_ERROR_INVALID_OPERATION 2

double DoIt (int TypeWork, double OperandA, double OperandB, int &ErrorCode);


#endif