#ifndef TEXT_H
#define TEXT_H

struct Text
{
    int size;
    size_t maxsize;
    char *data;
};

int Text_init(struct Text *txt, size_t maxsize);
int Text_overflow(struct Text *txt);
int Text_handle_overflow(struct Text *txt);
int Text_append_char(char c, struct Text *txt);

#endif
