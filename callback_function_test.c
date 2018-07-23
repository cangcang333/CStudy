/*************************************************************************
	> File Name: callback_function_test.c
	> Author: 
	> Mail: 
	> Created Time: 一  7/23 15:44:32 2018
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Function pointer structure */
typedef struct _OP
{
    float (*p_add) (float, float);
    float (*p_sub) (float, float);
    float (*p_mul) (float, float);
    float (*p_div) (float, float);
} OP;

/* add, sub, multiply and division function */
float ADD(float a, float b)
{
    return a + b;
}
float SUB(float a, float b)
{
    return a - b;
}
float MUL(float a, float b)
{
    return a * b;
}
float DIV(float a, float b)
{
    return a / b;
}

/* Initialize function pointer */
void init_op(OP *op)
{
    op->p_add = ADD;
    op->p_sub = SUB;
    op->p_mul = &MUL;
    op->p_div = &DIV;
}

/* Library function */
float add_sub_mul_div(float a, float b, float(*op_func)(float, float))
{
    return (*op_func)(a, b);
}

int main(int argc, char *argv[])
{
    OP *op = (OP *)malloc(sizeof(OP));
    init_op(op);

    /* Use function pointer directly */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", (op->p_add)(1.3, 2.2), (op->p_sub)(1.3, 2.2), (op->p_mul)(1.3, 2.2), (op->p_div)(1.3, 2.2));

    /* Use callback function */
    printf("ADD = %f, SUB = %f, MUL = %f, DIV = %f\n", 
          add_sub_mul_div(1.3, 2.2, ADD),
          add_sub_mul_div(1.3, 2.2, SUB),
          add_sub_mul_div(1.3, 2.2, MUL),
          add_sub_mul_div(1.3, 2.2, DIV));
}
