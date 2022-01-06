#ifndef CALCULATOR_OPERATION_H
#define CALCULATOR_OPERATION_H

typedef struct Operation
{
    double left;
    double right;
    double (*operator)(double, double);
} Operation;

double OperationApply(Operation *operation);

double Plus(double left, double right);

double Minus(double left, double right);

double Multiply(double left, double right);

double Divide(double left, double right);

#endif