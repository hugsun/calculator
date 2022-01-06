#include <stdio.h>
#include <string.h>
#include "console_ui.h"
#include "unit_test_ui.h"
#include "gtk_ui.h"

int main(int argc, char *argv[])
{
    printf("calculator start!\n");
    if (argc > 1)
    {
        if (strcasecmp(argv[1], "console") == 0)
        {
            RunConsoleUi(argc, argv);
        }
        else if (strcasecmp(argv[1], "ut") == 0)
        {
            RunUnitTestUi(argc, argv);
        }
    }
    else
    {
        RunGtkUi(argc, argv);
    }
    return 0;
}