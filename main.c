#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "pxtoem.h"
#include "Text.h"

int main(int argc, char **argv)
{
    FILE *input = stdin;
    FILE *output = stdout;
    struct Text txt, converted;

    txt = get_text(input);
    converted = convert(txt);
    free(txt.data);
    return 0;
}

