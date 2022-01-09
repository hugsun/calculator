#include "calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ClearCalcContextInputBuffer(CalcContext *context)
{
    context->input_buffer[0] = 0;
    context->input_buffer_position = 0;
}

static void ClearCalcContext(CalcContext *context)
{
    ClearCalcContextInputBuffer(context);
    context->result = 0;
    memset(&context->previous_operation, 0, sizeof(Operation));
    memset(&context->current_operation, 0, sizeof(Operation));
}

CalcContext *CreateCalcContext()
{
    CalcContext *context = malloc(sizeof(CalcContext));
    ClearCalcContext(context);
    return context;
}

void DestroyCalcContext(CalcContext **p_context)
{
    free(*p_context);
    *p_context = NULL;
}

static void FormatInput(CalcContext *context)
{
    if (context->input_buffer_position == 0)
    {
        context->input_buffer[0] = '0';
        context->input_buffer[1] = 0;
        context->input_buffer_position = 1;
    }
    else if (context->input_buffer_position == 1)
    {
        if (context->input_buffer[0] == '.')
        {
            context->input_buffer[0] = '0';
            context->input_buffer[1] = '.';
            context->input_buffer[2] = 0;
            context->input_buffer_position = 2;
        }
    }
    else if (context->input_buffer_position > 1)
    {
        char *p = context->input_buffer;
        // if (p[0] == '0' && p[1] != '.')
        // {
        //     p[0] = p[1];
        //     p[1] = 0;
        //     context->input_buffer_position = 1;
        // }
        if (p[context->input_buffer_position - 1] == '.')
        {
            for (int i = 0; i < context->input_buffer_position - 1; i++)
            {
                if (p[i] == '.')
                {
                    context->input_buffer_position--;
                    p[i] = 0;
                    break;
                }
            }
        }
    }
}

static void DisplayInput(CalcContext *context)
{
    FormatInput(context);
    context->display_text(context->input_buffer);
}

static void FormatOutput(CalcContext *context)
{
    if (context->result == -0.0)
    {
        context->result = 0.0;
    }
    sprintf(context->input_buffer, "%.6g", context->result);
}

static void DisplayOutput(CalcContext *context)
{
    FormatOutput(context);
    context->display_text(context->input_buffer);
    ClearCalcContextInputBuffer(context);
}

static void ApplyInput(CalcContext *context, double *opreand)
{
    if (context->input_buffer_position > 0)
    {
        *opreand = atof(context->input_buffer);
        ClearCalcContextInputBuffer(context);
    }
    else
    {
        *opreand = context->result;
    }
}

static void ApplyInputToLeft(CalcContext *context)
{
    ApplyInput(context, &context->current_operation.left);
}

static void ApplyInputToRight(CalcContext *context)
{
    ApplyInput(context, &context->current_operation.right);
}

static void ApplyPreviousOperation(CalcContext *context)
{
    context->result = OperationApply(&context->previous_operation);
}

static void ApplyCurrentOperation(CalcContext *context)
{
    context->result = OperationApply(&context->current_operation);
    memcpy(&context->previous_operation, &context->current_operation,
           sizeof(Operation));
    memset(&context->current_operation, 0, sizeof(Operation));
}

int HandleInput(CalcContext *context, char input_value)
{
    if (input_value)
    {
        switch (input_value)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
        {
            if (context->input_buffer_position < MAX_CHAR)
            {
                context->input_buffer[context->input_buffer_position++] = input_value;
                context->input_buffer[context->input_buffer_position] = '\0';
            }
            DisplayInput(context);
            break;
        }
        case 'C':
            ClearCalcContext(context);
            DisplayInput(context);
            break;
        case '%':
            ApplyInputToLeft(context);
            context->current_operation.operator= Divide;
            context->current_operation.right = 100;
            ApplyCurrentOperation(context);
            DisplayOutput(context);
            break;
        case '+':
            context->current_operation.operator= Plus;
            ApplyInputToLeft(context);
            break;
        case '-':
            context->current_operation.operator= Minus;
            ApplyInputToLeft(context);
            break;
        case '*':
            context->current_operation.operator= Multiply;
            ApplyInputToLeft(context);
            break;
        case '/':
            context->current_operation.operator= Divide;
            ApplyInputToLeft(context);
            break;
        case '=':
            if (context->current_operation.operator)
            {
                ApplyInputToRight(context);
                ApplyCurrentOperation(context);
                DisplayOutput(context);
            }
            else if (context->previous_operation.operator)
            {
                context->previous_operation.left = context->result;
                ApplyPreviousOperation(context);
                DisplayOutput(context);
            }
            else
            {
                printf("No operation.\n");
            }
            break;
        case 'S':
            ApplyInputToLeft(context);
            context->current_operation.operator= Multiply;
            context->current_operation.right = -1;
            ApplyCurrentOperation(context);
            DisplayOutput(context);
            break;
        }
    }
    return 1;
}