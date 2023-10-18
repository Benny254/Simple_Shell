#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

int chk_interactive(siginfo_t *sh_info);
int _delim(char ch, char *d);
int is_upper(int ch);
int convert_string(char *str);
char *change_number(long int n, int b, int f);

int string_convert(char *str);
void print_err(siginfo_t *sh_info, char *s);
void prints_string(char *s);
int dec_print(int in, int fd);
void rm_comment(char *addr);

int eprintch(char ch);
int write_ch(char ch, int fd);
int pfd_input(char *s, int fd);
char *cp_char(char *p_str, int a, int b);
int free_p(void **p);

int chk_filetype(siginfo_t *sh_info, char *filepath);
char *chk_cmd(siginfo_t *sh_info, char *p_str, char *cmd);

int do_exit(siginfo_t *sh_info);
int change_dir(siginfo_t *sh_info);
int help_func(siginfo_t *sh_info);
int disp_hist(siginfo_t *sh_info);
int new_str(char **a, char *b);

int alias_string(siginfo_t *sh_info, char *s);
int alias_set(siginfo_t *sh_info, char *s);
int alias_rp(siginfo_t *sh_info);
int alias_prt; typedef struct sh_list_t *node;
int get_alias(siginfo_t *sh_info);
#endif
