#include "operation.h"

double OperationApply(Operation *operation)
{
    if (operation->operator)
    {
        return operation->operator(operation->left, operation->right);
    }
    else
    {
        return 0.0;
    }
}

double Plus(double left, double right)
{
    return left + right;
}

double Minus(double left, double right)
{
    return left - right;
}

double Multiply(double left, double right)
{
    return left * right;
}

double Divide(double left, double right)
{
    // 如果在计算过程中判断浮点数，需要判断其是否小于一个精度误差的最小值
    // fabsf(float_value) < 1e-6
    // fabs(double_value) < 1e-15
    // 此处为用户输入值，所以可以直接这么比较
    if (right == 0.0)
    {
        return 0;
    }
    else
    {
        return left / right;
    }
}