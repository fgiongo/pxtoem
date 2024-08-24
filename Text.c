#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Text.h"

int Text_init(struct Text *txt)
{
    txt->size = 0;
    txt->maxsize = 0;
    txt->data = malloc(TEXT_INIT_BUFSIZE);
    if (txt->data)
    {
        txt->maxsize = TEXT_INIT_BUFSIZE - 1;
        txt->data[0] = '\0';
        return TEXT_SUCCESS;
    }
    return TEXT_ERR_BADALLOC;
}

int Text_overflow(struct Text *txt)
{
    size_t new_bufsize = 2 * (txt->maxsize + 1);
    char *new_data = realloc(txt->data, new_bufsize);
    if (new_data)
    {
        txt->data = new_data;
        txt->maxsize = new_bufsize - 1;
        return TEXT_SUCCESS;
    }
    return TEXT_ERR_BADALLOC;
}

int Text_append_char(char c, struct Text *txt)
{
    if (txt->size == txt->maxsize)
    {
        if (Text_overflow(txt) != TEXT_SUCCESS)
        {
            return TEXT_ERR_BADALLOC;
        }
    }
    txt->data[txt->size] = c;
    txt->size++;
    txt->data[txt->size + 1] = '\0';
    return TEXT_SUCCESS;
}

int Text_append_str(char *str, struct Text *txt, size_t n)
{
    while ((txt->size + n) > txt->maxsize)
    {
        if (Text_overflow(txt) != TEXT_SUCCESS)
        {
            return TEXT_ERR_BADALLOC;
        }
    }
    memcpy(&(txt->data[txt->size]), str, n);
    txt->size += n;
    txt->data[txt->size + 1] = '\0';
    return TEXT_SUCCESS;
}
