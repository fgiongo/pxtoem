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
    int emsize = 16;
    txt = read_file(input);
    converted = convert_px_to_em(txt, emsize);
    fputs(converted.data, output);
    free(txt.data);
    return 0;
}

