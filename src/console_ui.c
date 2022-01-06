#include "console_ui.h"
#include <stdlib.h>
#include <stdio.h>

UiContext *ui_context;

void DisplayConsoleText(char *text)
{
    fputs(text, ui_context->text_displayer);
    fputc('\n', ui_context->text_displayer);
    fflush(ui_context->text_displayer);
}

static void InitConsole()
{
    ui_context = malloc(sizeof(UiContext));
    ui_context->text_displayer = stdout;
    ui_context->calc_context = CreateCalcContext();
    ui_context->calc_context->display_text = DisplayConsoleText;
}

static void DestroyConsole()
{
    DestroyCalcContext(&ui_context->calc_context);
    free(ui_context);
    ui_context = NULL;   
}

static void ConsoleMain()
{
    int next_input = getchar();
    while (next_input != EOF && next_input != 'q' && next_input != 'Q')
    {
        HandleInput(ui_context->calc_context, next_input);
        next_input = getchar();
    }
    puts("Thank you");
}

int RunConsoleUi(int argc, char *argv[])
{
    InitConsole();
    ConsoleMain();
    DestroyConsole();
    return 0;
}