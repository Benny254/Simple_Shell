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

int chk_interactive(info_t *info);
int _delim(char ch, char *d);
int is_upper(int ch);
int convert_string(char *str);
char *change_number(long int n, int b, int f);

int string_convert(char *str);
void print_err(sh_info_t *info, char *s);
void prints_string(char *s);
int dec_print(int in, int fd);
void rm_comment(char *addr);

int eprintch(char ch);
int write_ch(char ch, int fd);
int pfd_input(char *s, int fd);
char *cp_char(char *p_str, int a, int b);
int free_p(void **p);

int chk_filetype(*info, char *filepath);
char *chk_cmd(info_t *info, char *p_str, char *cmd);
char *chk_start(const char *haystack, const char *needle);
char *cat_str(char *add_to, char *add_from);
int len_str(char *st);

int do_exit(info_t *info);
int change_dir(info_t *info);
int help_func(info_t *info);
int disp_hist(info_t *info);
int new_str(char **a, char *b);

int alias_string(info_t *info, char *s);
int alias_set(info_t *info, char *s);
int alias_rp(info_t *info);
int alias_prt(list_t *node);
int get_alias(info_t *info);

char *cpy_str(char *d, char *s);
char *dupstr(const char *st);
void print_str(char *s);
int printch(char c);
int comp_str(char *s1, char *s2);

list_t *new_node(list_t **head, const char *str, int num);
list_t *node_add(sh_list_t **head, const char *str, int num);
size_t str_print(const sh_list_t *h);
int node_delete(sh_list_t **head, unsigned int index);
void node_free(sh_list_t **h_ptr);

char **str_array(list_t *head);
size_t elem_list(const list_t *h);
list_t *node_start(list_t *node, char *p, char c);
ssize_t node_get(list_t *h, list_t *node);
size_t len_list(const list_t *h);

char **string_split(char *str, char d);
char **str_split(char *str, char *d);
void *allocmem(void *ptr, unsigned int a, unsigned int b);
char *bytemem(char *s, char b, unsigned int n);
void free_str(char **k);

int _myenv(info_t *info);
char *env_var(info_t *info, const char *name);
int init_env(info_t *info);
int rem_env(info_t *info);
int envpop(info_t *info);

ssize_t buf_input(info_t *info, char **buff, size_t *len);
ssize_t type_in(info_t *info);
ssize_t bufread(info_t *info, char *buff, size_t *s);
int nextline(info_t *info, char **ptr, size_t *length);
void handlec(__attribute__((unused))int s);

char *file_hist(info_t *info);
int histfile(info_t *info);
int histread(info_t *info);
int list_hist(info_t *info, char *buff, int linecount);
int histnum(info_t *info);

char **envstr(info_t *info);
int rem_venv(info_t *info, char *v);
int init_evar(info_t *info, char *v, char *value);
void int_info(info_t *info, char **v);
void infofr(info_t *info, int f);

void infoclr(info_t *info);
char *cppy_str(char *dest, char *src, int ch);
char *concat_str(char *dest, char *src, int by);
char *_strchr(char *s, char ch);

int testchain(info_t *info, char *buff, size_t *p);
void chainchk(info_t *info, char *buff, size_t *p, size_t i, size_t l);
int vars_rp(info_t *info);

int _shell(info_t *info, char **av);
int builtincmd(info_t *info);
void cmd_find(info_t *info);
void run_cmd(info_t *info);


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
 * struct liststr - linked list
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
 *struct passinfo - contains pseudo-arguements to pass into function
 *allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@code_err: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@node_hist: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@fdinput: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int code_err;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *node_hist;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int fdinput;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains builtin string and related function
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(sh_info_t *);
} builtin_table;

#endif
