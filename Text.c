#include <stdlib.h>
#include <stdio.h>
#include "Text.h"

int Text_init(struct Text *txt, size_t maxsize)
{
    txt->size = 0;
    txt->maxsize = 0;
    txt->data = malloc(maxsize);
    if (txt->data)
    {
        txt->maxsize = maxsize;
        return 0;
    }
    return -1;
}

int Text_overflow(struct Text *txt)
{
    char *new_data;
    size_t new_maxsize;

    new_maxsize = 2 * txt->maxsize;
    new_data = realloc(txt->data, new_maxsize);
    if (new_data)
    {
        txt->data = new_data;
        txt->maxsize = new_maxsize;
        return 0;
    }
    return -1;
}

int Text_handle_overflow(struct Text *txt)
{
    if (txt->size == txt->maxsize)
    {
        if (Text_overflow(txt) != 0)
        {
            return -1;
        }
    }
    return 0;
}

int Text_append_char(char c, struct Text *txt)
{
    if (Text_handle_overflow(txt) != 0)
    {
        return -1;
    }
    txt->data[txt->size] = c;
    txt->size++;
    return 0;
}

