#include <stdio.h>
#include "../lib/my_math_lib.h"

int main (int argc, char** argv)
{
    double res;
    int err;
    // plus
 
    res=DoIt(LMM_OPERATION_PLUS, 66.666, 33.333, err);
    if(err==LMM_NO_ERROR)
    {
        if(res==(66.666+33.333))
        {
            printf("Test plus: OK %f\n", res);
        }
        else
        {
            printf("Test plus: error result %f\n", res);
        }
    }
    else
    {
        printf("Test plus: error\n");
    }

    //----------------------------------------------------------
    // minus

    res=DoIt(LMM_OPERATION_MINUS, -33.333, 77.777, err);
    if(err==LMM_NO_ERROR)
    {
        if(res==((-33.333)-77.777))
        {
            printf("Test minus: OK %f\n", res);
        }
        else
        {
            printf("Test minus: error result %f\n", res);
        }
    }
    else
    {
        printf("Test minus: error\n");
    }
    //----------------------------------------------------------
    // multiply
    res=DoIt(LMM_OPERATION_MULTIPLY, 12345679.0, 9.0, err);
    if(err==LMM_NO_ERROR)
    {
        if(res==(12345679.0*9.0))
        {
            printf("Test multiply: OK %f\n", res);
        }
        else
        {
            printf("Test multiply: error result %f\n", res);
        }
    }
    else
    {
        printf("Test multiply: error\n");
    }
    //----------------------------------------------------------
    // divide
    res=DoIt(LMM_OPERATION_DIVIDE, 111111111.0, 9.0, err);
    if(err==LMM_NO_ERROR)
    {
        if(res==(111111111.0/9.0))
        {
            printf("Test divide: OK %f\n", res);
        }
        else
        {
            printf("Test divide: error result %f\n", res);
        }
    }
    else
    {
        printf("Test divide: error\n");
    }
    //----------------------------------------------------------
    // error
    res=DoIt(47, 111111111.0, 9.0, err);
    if(err==LMM_NO_ERROR)
    {
        printf("Test invalid operation: error\n");
    }
    else
    {
        if(err==LMM_ERROR_INVALID_OPERATION)
        {
            printf("Test invalid operation: OK\n");
        }
        else
        {
            printf("Test invalid operation: invalid error\n");
        }
    }
    
    res=DoIt(LMM_OPERATION_DIVIDE, 111111111.0, 0.0, err);
    if(err==LMM_NO_ERROR)
    {
        printf("Test division by zero: error \n");
    }
    else
    {
        if(err==LMM_ERROR_DIVISION_BY_ZERO)
        {
            printf("Test division by zero: OK\n");
        }
        else
        {
            printf("Test division by zero: invalid error\n");
        }
    }
    
    
    
}




