#include "main.h"

/**
 * str_array - return array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **str_array(sh_list_t *head)
{
	sh_list_t *node = head;
	size_t a = len_list(head), b;
	char **strs;
	char *str;

	if (!head || !i)
	return (NULL);

	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
	return (NULL);

	a = 0;
	while (node)
	{
	str = malloc(len_str(node->str) + 1);
	if (!str)
	{
	for (b = 0; b < a; b++)
		free(strs[b]);
		free(strs);
			return (NULL);
	}

	str = cpy_str(str, node->str);
	strs[a] = str;

	node = node->next;
	a++;
	}

	strs[a] = NULL;
	return (strs);
}

/**
 * elem_list - print all elements of a linked list
 * @h: pointer to first node
 * Return: the size of list
 */
size_t elem_list(const sh_list_t *h)
{
	size_t a = 0;

	for (; h; h = h->next)
	{
		print_str(change_number(h->num, 10, 0));
		printch(':');
		printch(' ');
		print_str(h->str ? h->str : "(nil)");
		print_str("\n");
		a++;
	}

	return (a);
}

/**
 * node_start - return node whose string starts with prefix
 * @node: pointer to be listed head
 * @p: string to match
 * @c: next char after prefix to match
 * Return: to match node or null
 */
sh_list_t *node_start(sh_list_t *node, char *p, char c)
{
	char *pt = NULL;

	while (node)
	{
		pt = chk_start(node->str, p);
		if (pt && ((c == -1) || (*pt == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_get - get the index of a node
 * @h: pointer to list a head
 * @node: the pointer to the node
 * Return: an index of node or -1
 */
ssize_t node_get(sh_list_t *h, list_t *node)
{
	size_t l;

	for (l = 0; h; h = h->next, l++)
	{
	if (h == node)
		return (l);
	}

	return (-1);
}

/**
 * len_list - determine length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t len_list(const sh_list_t *h)
{
	size_t a = 0;

	for (; h; h = h->next)
	{
		a++;
	}

	return (a);
}
