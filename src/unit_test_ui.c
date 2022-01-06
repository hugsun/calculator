#include "unit_test_ui.h"
#include "calculator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

UiContext *ui_context;

static void DisplayTextToBuffer(char *text)
{
    sprintf(ui_context->text_displayer, "%s", text);
}

static void InitUnitTest()
{
    char *const kOutputBuffer = malloc(MAX_CHAR + 1);

    ui_context = malloc(sizeof(UiContext));
    ui_context->text_displayer = kOutputBuffer;
    ui_context->calc_context = CreateCalcContext();
    ui_context->calc_context->display_text = DisplayTextToBuffer;
}

static void DestroyUnitTest()
{
    DestroyCalcContext(&ui_context->calc_context);
    free(ui_context->text_displayer);
    free(ui_context);
    ui_context = NULL;
}

static void UnitTestMain()
{
    FILE *case_file = fopen("tests/cases.txt", "r");
    if (case_file)
    {
        char key;
        char output_result[MAX_CHAR + 1];
        while (fscanf(case_file, " %c,%s", &key, output_result) != EOF)
        {
            if (HandleInput(ui_context->calc_context, key))
            {
                if (strcmp(output_result, ui_context->text_displayer) == 0)
                {
                    printf("Input [%c]: Output %s, Pass\n", key, output_result);
                }
                else
                {
                    printf("Input [%c]: Output %s, Fail\n", key, (char *)ui_context->text_displayer);
                }
            }
        }
    }
    else
    {
        perror("open case file");
    }
}

int RunUnitTestUi(int argc, char *argv[])
{
    InitUnitTest();
    UnitTestMain();
    DestroyUnitTest();
    return 0;
}