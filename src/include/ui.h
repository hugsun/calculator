#ifndef CALCULATOR_UI_H
#define CALCULATOR_UI_H

#include "calculator.h"

typedef struct
{
    void *text_displayer;
    CalcContext *calc_context;
} UiContext;
#endif