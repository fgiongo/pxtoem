#ifndef PXTOEM_H
#define PXTOEM_H

#define MATCH_FAIL -1
#define STRBUFSIZE 64

void error(const char *errmsg, unsigned char errcode);
struct Text read_file(FILE *fp);
void try_Text_init(struct Text *txt);
void try_Text_append_char(char c, struct Text *txt);
void try_Text_append_str(char *str, struct Text *txt, size_t n);
struct Text convert_px_to_em(const struct Text txt, float emsize);
int parse_dec(const char *str, int len);
int parse_dec_int(const char *str, int len);
int match_any_char(const char *str, int str_len, const char *ch, int ch_len);

#endif
