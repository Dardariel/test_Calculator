#include "my_math_lib.h"

double DoIt (int TypeWork, double OperandA, double OperandB, int &ErrorCode)
{
    
    // double = -9 223 372 036 854 775 808 .0   /   9 223 372 036 854 775 807.0
    
    ErrorCode=LMM_NO_ERROR;
    switch(TypeWork)
    {
        case 1: //+
            return OperandA+OperandB;
        case 2: // -
            return OperandA-OperandB;
        case 3: // *
            return OperandA*OperandB;
        case 4: // /
            if(OperandB==0.0)
            {
                ErrorCode=LMM_ERROR_DIVISION_BY_ZERO;
                return 0;
            }
            else
            {
                return OperandA/OperandB;
            }
        default:
            ErrorCode=LMM_ERROR_INVALID_OPERATION;
            return 0;
    }
}