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

int chk_interactive(sh_info_t *sh_info);
int _delim(char ch, char *d);
int is_upper(int ch);
int convert_string(char *str);
char *change_number(long int n, int b, int f);

int string_convert(char *str);
void print_err(sh_info_t *sh_info, char *s);
void prints_string(char *s);
int dec_print(int in, int fd);
void rm_comment(char *addr);

int eprintch(char ch);
int write_ch(char ch, int fd);
int pfd_input(char *s, int fd);
char *cp_char(char *p_str, int a, int b);
int free_p(void **p);

int chk_filetype(*sh_info, char *filepath);
char *chk_cmd(sh_info_t *sh_info, char *p_str, char *cmd);
char *chk_start(const char *haystack, const char *needle);
char *cat_str(char *add_to, char *add_from);
int len_str(char *st);

int do_exit(sh_info_t *sh_info);
int change_dir(sh_info_t *sh_info);
int help_func(sh_info_t *sh_info);
int disp_hist(sh_info_t *sh_info);
int new_str(char **a, char *b);

int alias_string(sh_info_t *sh_info, char *s);
int alias_set(sh_info_t *sh_info, char *s);
int alias_rp(sh_info_t *sh_info);
int alias_prt(sh_list_t *node);
int get_alias(sh_info_t *sh_info);

char *cpy_str(char *d, char *s);
char *dupstr(const char *st);
void print_str(char *s);
int printch(char c);
int comp_str(char *s1, char *s2);

sh_list_t *new_node(sh_list_t **head, const char *str, int num);
sh_list_t *node_add(sh_list_t **head, const char *str, int num);
size_t str_print(const sh_list_t *h);
int node_delete(sh_list_t **head, unsigned int index);
void node_free(sh_list_t **h_ptr);

char **str_array(sh_list_t *head);
size_t elem_list(const sh_list_t *h);
sh_list_t *node_start(sh_list_t *node, char *p, char c);
ssize_t node_get(sh_list_t *h, list_t *node);
size_t len_list(const sh_list_t *h);

#endif
