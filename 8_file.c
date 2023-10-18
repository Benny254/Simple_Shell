#include "main.h"

/**
 * new_node - add node to start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: list size
 */
struct *new_node(struct **head, const char *str, int num)
{
	sh_list_t *first;

	if (!head)
		return (NULL);

	first = malloc(sizeof(sh_list_t));
	if (!first)
	return (NULL);

	bytemem((void *)first, 0, sizeof(sh_list_t));
	first->num = num;

	if (str)
	{
	first->str = dupstr(str);
	if (!first->str)
		{
		free(first);
			return (NULL);
		}
	}
	else
	{
		first->str = NULL;
	}

	first->next = *head;
	*head = first;

	return (first);
}

/**
 * node_add - add a node to the end of the list
 * @head: address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 * Return: the size of list
 */
struct *node_add(struct **head, const char *str, int num)
{
	list_t *last, *node;

	if (!head)
		return (NULL);

	node = *head;
	last = malloc(sizeof(sh_list_t));
	if (!last)
		return (NULL);

	bytemem((void *)last, 0, sizeof(sh_list_t));
	last->num = num;

	if (str)
	{
	last->str = dupstr(str);
	if (!last->str)
	{
		free(last);
			return (NULL);
	}
	}
	if (node)
	{
	for (; node->next; node = node->next)
		node->next = last;
	}
	else
	{
		*head = last;
	}

	return (last);
}

/**
 * str_print - print only the str element of a list_t linked list
 * @h: the pointer to first node
 * Return: the size of list
 */
size_t str_print(const sh_list_t *h)
{
	size_t a;

	for (a = 0; h; h = h->next, a++)
	{
		print_err(h->str ? h->str : "(nil)");
		print_err(psiginfo,"\n");
	}

	return (a);
}

/**
 * node_delete - delete node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 otherwise
 */
int node_delete(struct sh_list_t **head, unsigned int index)
{
	struct *node, *prev;
	unsigned int l;

	if (!head || !*head)
	return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	prev = *head;
	for (l = 0, nd = (*head)->nxt; nd; l++, prev = nd, nd = nd->nxt)
	{
	if (l == index)
		{
		prev->next = node->next;
		free(node->str);
		free(node);
			return (1);
		}
	}

	return (0);
}

/**
 * node_free - free all nodes of a list
 * @h_ptr: an address of pointer to head node
 * Return: void
 */
void node_free(sh_list_t **h_ptr)
{
	sh_list_t *node, *next_node, *head;

	if (!h_ptr || !*h_ptr)
	return;

	head = *h_ptr;
	node = head;

	for (; node; node = next_node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
	}

	*h_ptr = NULL;
}
