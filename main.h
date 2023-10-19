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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/** File 1 */
int chk_interactive(info_t *info);
int delimch(char c, char *delim);
int is_upper(int c);
int convert_string(char *s);
char *change_number(long int num, int base, int flags);

/** File 2 */
int string_convert(char *s);
void print_err(info_t *info, char *estr);
void prints_string(char *str);
int dec_print(int input, int fd);
void rm_comment(char *buf);

/** File 3 */
int eprintch(char c);
int write_ch(char c, int fd);
int pfd_input(char *str, int fd);
char *cp_char(char *pathstr, int start, int stop);
int free_p(void **ptr);

/** File 4 */
int chk_filetype(info_t *info, char *path);
char *chk_cmd(info_t *info, char *pathstr, char *cmd);
char *cat_str(char *dest, char *src);
char *chk_start(const char *haystack, const char *needle);
int len_str(char *s);

/** File 5 */
int do_exit(info_t *info);
int change_dir(info_t *info);
int help_func(info_t *info);
int disp_hist(info_t *info);
int new_str(char **old, char *new);

/** File 6 */
int alias_reset(info_t *info, char *str);
int alias_set(info_t *info, char *str);
int alias_rp(info_t *info);
int alias_prt(list_t *node);
int get_alias(info_t *info);

/** File 7 */
char *cpy_str(char *dest, char *src);
char *dupstr(const char *str);
void print_str(char *str);
int printch(char c);
int comp_str(char *s1, char *s2);

/** File 8 */
list_t *new_node(list_t **head, const char *str, int num);
list_t *node_add(list_t **head, const char *str, int num);
size_t str_print(const list_t *h);
int node_delete(list_t **head, unsigned int index);
void node_free(list_t **head_ptr);

/** File 9 */
char **str_array(list_t *head);
size_t elem_list(const list_t *h);
list_t *node_start(list_t *node, char *prefix, char c);
ssize_t node_get(list_t *head, list_t *node);
size_t len_list(const list_t *h);

/** File 10 */
char **string_split(char *str, char d);
char **str_split(char *str, char *d);
void *allocmem(void *ptr, unsigned int old_size, unsigned int new_size);
char *bytemem(char *s, char b, unsigned int n);
void free_str(char **pp);

/** File 11 */
int prtenv(info_t *info);
char *env_var(info_t *info, const char *name);
int init_env(info_t *info);
int rem_env(info_t *info);
int envpop(info_t *info);

/** File 12 */
ssize_t buf_input(info_t *info, char **buf, size_t *len);
ssize_t type_in(info_t *info);
ssize_t bufread(info_t *info, char *buf, size_t *i);
int nextline(info_t *info, char **ptr, size_t *length);
void handlec(__attribute__((unused))int sig_num);

/** File 13 */
char *file_hist(info_t *info);
int histfile(info_t *info);
int histread(info_t *info);
int list_hist(info_t *info, char *buf, int linecount);
int histnum(info_t *info);

/** File 14 */
char **envstr(info_t *info);
int rem_venv(info_t *info, char *var);
int init_evar(info_t *info, char *var, char *value);
void int_info(info_t *info, char **av);
void infofr(info_t *info, int all);

/** File 15 */
void infoclr(info_t *info);
char *cppy_str(char *dest, char *src, int n);
char *concat_str(char *dest, char *src, int n);
char *loc_ch(char *s, char c);

/** File 16 */
int testchain(info_t *info, char *buf, size_t *p);
void chainchk(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int vars_rp(info_t *info);

/** File 17 */
int _shell(info_t *info, char **av);
int builtincmd(info_t *info);
void cmd_find(info_t *info);
void run_cmd(info_t *info);

#endif
