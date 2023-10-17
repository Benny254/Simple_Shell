#include "main.h"

/**
 * list_len - to determine length of linked list
 * @h: the pointer to first node
 *
 * Return: the size of list
 */
size_t list_len(const list_t *h)
{
	size_t y = 0;

	for (; h; h = h->next)
	{
	y++;
	}

	return (y);
}

/**
 * list_to_strings - to return an array of strings of the list->str
 * @head: the pointer to first node
 *
 * Return: an array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !i)
	return (NULL);

	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
	return (NULL);

	x = 0;
	while (node)
	{
	str = malloc(_strlen(node->str) + 1);
	if (!str)
	{
	for (y = 0; y < x; y++)
		free(strs[y]);
		free(strs);
			return (NULL);
	}

	str = _strcpy(str, node->str);
	strs[x] = str;

	node = node->next;
	x++;
	}

	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - to print all elements of a list_t linked list
 * @h: the pointer to first node
 *
 * Return: the size of list
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	for (; h; h = h->next)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		x++;
	}

	return (x);
}

/**
 * node_starts_with - to return node whose string starts with prefix
 * @node: the pointer to be listed head
 * @prefix: the string to match
 * @c: the next char after prefix to match
 *
 * Return: to match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - to get the index of a node
 * @head: the pointer to list a head
 * @node: the pointer to the node
 *
 * Return: an index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	for (i = 0; head; head = head->next, i++)
	{
	if (head == node)
		return (i);
	}

	return (-1);
}
