#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pxtoem.h"
#include "Text.h"

void error(const char *errmsg, unsigned char errcode)
{
    fputs("CRITICAL ERROR: ", stderr);
    fputs(errmsg, stderr);
    exit(errcode);
}

struct Text read_file(FILE *fp)
{
    int c;
    struct Text txt;
    try_Text_init(&txt);
    while ((c = fgetc(fp)) != EOF)
    {
        try_Text_append_char(c, &txt);
    }
    return txt;
}

void try_Text_init(struct Text *txt)
{
    char *errmsg = "Text_init: bad alloc\n";
    if (Text_init(txt) != TEXT_SUCCESS)
    {
        error(errmsg, 1);
    }
}

void try_Text_append_char(char c, struct Text *txt)
{
    char *errmsg = "Text_append_char: bad alloc\n";
    if (Text_append_char((char) c, txt) != TEXT_SUCCESS)
    {
        error(errmsg, 1);
    }
}

void try_Text_append_str(char *str, struct Text *txt, size_t n)
{
    char *errmsg = "Text_append_str: bad alloc\n";
    if (Text_append_str(str, txt, n) != TEXT_SUCCESS)
    {
        error(errmsg, 1);
    }
}

// How the sausage is made (messy but efficient)
struct Text convert_px_to_em(const struct Text txt, float emsize)
{
    struct Text out;
    try_Text_init(&out);
    if ((emsize == 0.0))
    {
        error("convert_px_to_em: emsize cannot be zero\n", 1);
    }
    size_t i = 0, len = txt.size, numlen;
    int match;
    float num;
    char converted[STRBUFSIZE];
    // match gets index of next decimal digit (or '.') in input text
    while (i < txt.size
           && (match = match_any_char(&txt.data[i], len, ".0123456789", 11))
           != MATCH_FAIL)
    {
        // Copy input text to output up until match index
        try_Text_append_str(&txt.data[i], &out, match);
        // Consume processed input
        i += match;
        len -= match;
        // If we have found a number
        if((numlen = parse_dec(&txt.data[i], len)))
        {
            // If it is a valid px value
            if (txt.size > i + numlen + 1
                && txt.data[i + numlen] == 'p'
                && txt.data[i + numlen + 1] == 'x')
            {
                // Convert it
                num = strtof(&txt.data[i], NULL);
                num /= emsize;
                snprintf(converted, STRBUFSIZE, "%.4f", num);
                // Consume processed input
                i += numlen + 2;
                len -= numlen + 2;
                // Write it to output
                numlen = strlen(converted);
                try_Text_append_str(converted, &out, numlen);
                try_Text_append_str("em", &out, 2);
            }
            else // Is a number but not a px value
            {
                // Copy number to output
                try_Text_append_str(&txt.data[i], &out, numlen);
                // Consume processed input
                i += numlen;
                len -= numlen;
            }
        }
        else // Isn't a number, matched a '.'
        {
            // Write it to output
            try_Text_append_char(txt.data[i], &out);
            // Consume input
            i++;
            len--;
        }
        // No more matches, copy whatever is left
    }
    if (i < txt.size)
    {
        try_Text_append_str(&txt.data[i], &out, txt.size - i);
    }
    return out;
}

// If str points to a rational number in decimal representation (int or float
// in conventional notation) the funtion retuns number of characters of the
// representation, otherwise returns 0;
int parse_dec(const char *str, int len)
{
    int int_len, frac_len;
    if (len <= 0)
    {
        return 0;
    }

    // Match the integer part of number
    int_len = parse_dec_int(str, len);

    // Try to match a decimal part
    if (len > int_len && str[int_len] == '.')
    {
        if (len > int_len + 1){
            frac_len = parse_dec_int(&str[int_len + 1], len - int_len - 1);
        }
        else
        {
            return int_len + 1;
        }
    }
    else
    {
        return int_len;
    }

    // Handle case where we only matched '.'
    if (int_len + frac_len == 0)
    {
        return 0;
    }
    else 
    {
        return int_len + frac_len + 1;
    }
}

// If str points to an integer in decimal representation the funtion retuns
// number of characters of the representation, otherwise returns 0;
int parse_dec_int(const char *str, int len)
{
    if (len <= 0)
    {
        return 0;
    }
    for (int i = 0; i < len; i++)
    {
        if (match_any_char(&str[i], 1, "0123456789", 10) == MATCH_FAIL)
        {
            return i;
        }
    }
    return 0;
}

// Searches str for any of the characters in ch, returns index of
// first value found, otherwise returns MATCH_FAIL;
int match_any_char(const char *str, int str_len, const char *ch, int ch_len)
{
    for (int i = 0; i < str_len; i++)
    {
        for (int j = 0; j < ch_len; j++)
        {
            if (str[i] == ch[j])
            {
                return i;
            }
        }
    }
    return MATCH_FAIL;
}
