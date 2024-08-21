#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pxtoem.h"
#include "Text.h"

void crash(const char *errmsg, unsigned char errcode)
{
    fputs(errmsg, stderr);
    exit(errcode);
}

struct Text get_text(FILE *fp)
{
    int c;
    struct Text txt;
    char *errmsg = "Error(get_text): bad alloc";

    if (Text_init(&txt, TEXT_INIT_SIZE) != 0)
    {
        crash(errmsg, 1);
    }

    c = fgetc(fp);
    while (c != EOF)
    {
        if (Text_append_char((char) c, &txt) != 0)
        {
            crash(errmsg, 2);
        }
        c = fgetc(fp);
    }

    if (Text_append_char('\0', &txt))
    {
        crash(errmsg, 2);
    }
    return txt;
}

// Does the thing!
struct Text convert(struct Text txt)
{
    struct Text out;
    int px_index, num_index, write_index;
    char px_num[BUF_SIZE], em_num[BUF_SIZE];
    
    Text_init(&out, TEXT_INIT_SIZE);

    // Get index of first occurrence of the string 'px'
    px_index = 0;
    px_index = find_px(txt, px_index);

    // Get index of number preceding pt_index, if exists
    // otherwise gets -1
    num_index = find_num(txt, px_index);

    // We need an index to copy text unrelated to any conversion
    write_index = 0;

    // This loop only gets executed if find_num finds a target
    while (num_index >= 0)
    {
        // Copy text unrelated to conversion to output
        // up until number to be converted
        append_txt(txt, &out, write_index, num_index);

        // Advance index past 'px' string
        write_index = px_index + 2;

        // Copy number to be converted, convert it, write it
        copy_px(txt, num_index, px_num);
        convert_px(px_num, em_num);
        write_em(em_num, &out);

        // Try to find next target
        // (will return -1 if it fails to find one)
        px_index = find_px(txt, px_index);

        // Could not find another 'px' string so exit loop
        if (px_index < 0)
        {
            break;
        }

        num_index = find_num(txt, px_index);
    }

    // No more targets, copy what's left and return it
    copy_until_end(txt, &out, write_index);
    return out;
}

int find_px(struct Text txt, int start_index)
{
    // TODO: implement this
    return 0;
}

int find_num(struct Text txt, int px_index)
{
    // TODO: implement this
    // remember to check for negatives
    return 0;
}

void append_txt(struct Text src, struct Text *dest, int start, int end)
{
    // TODO: implement this
}
void copy_px(struct Text src, int num_index, char *dest)
{
    // TODO: implement this
}
void convert_px(char *in_px, char *out_em)
{
    // TODO: implement this
}
void write_em(char *src, struct Text *dest)
{
    // TODO: implement this
}

void copy_until_end(struct Text src, struct Text *dest, int start)
{
    // TODO: implement this
}
