#ifndef PXTOEM_H
#define PXTOEM_H

#define TEXT_INIT_SIZE 2048
#define BUF_SIZE 32
#define EM_SIZE 16.0

void crash(const char *errmsg, unsigned char errcode);
struct Text get_text(FILE *fp);
struct Text convert(struct Text txt);
int find_px(struct Text txt, int start_index);
int find_num(struct Text txt, int px_index);
void append_txt(struct Text src, struct Text *dst, int start, int end);
void copy_px(struct Text src, int num_index, char *dest);
void convert_px(char *in_px, char *out_em);
void write_em(char *src, struct Text *dest);
void copy_until_end(struct Text src, struct Text *dest, int start);

#endif
