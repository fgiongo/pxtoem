#ifndef TEXT_H
#define TEXT_H

#define TEXT_SUCCESS 0
#define TEXT_ERR_BADALLOC -1
#define TEXT_INIT_BUFSIZE 1024

struct Text
{
    size_t size;
    size_t maxsize;
    char *data;
};

int Text_init(struct Text *txt);
int Text_overflow(struct Text *txt);
int Text_append_char(char c, struct Text *txt);
int Text_append_str(char *str, struct Text *txt, size_t n);

#endif
