#include "main.h"

/**
 * add_node - to add a node to the start of the list
 * @head: an address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 *
 * Return: the size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
	return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
	new_head->str = _strdup(str);
	if (!new_head->str)
		{
		free(new_head);
			return (NULL);
		}
	}
	else
	{
		new_head->str = NULL;
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - to add a node to the end of the list
 * @head: an address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 *
 * Return: the size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
	new_node->str = _strdup(str);
	if (!new_node->str)
	{
		free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
	for (; node->next; node = node->next)

		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_str - to print only the str element of a list_t linked list
 * @h: the pointer to first node
 *
 * Return: the size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t x;

	for (x = 0; h; h = h->next, x++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}

	return (x);
}

/**
 * delete_node_at_index - to delete node at given index
 * @head: an address of pointer to first node
 * @index: an index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j;

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

	prev_node = *head;
	for (j = 0, nd = (*head)->nxt; nd; j++, prev_nd = nd, nd = nd->nxt)
	{
	if (j == index)
		{
		prev_node->next = node->next;
		free(node->str);
		free(node);
			return (1);
		}
	}

	return (0);
}

/**
 * free_list - to free all nodes of a list
 * @head_ptr: an address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	return;

	head = *head_ptr;
	node = head;

	for (; node; node = next_node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
	}

	*head_ptr = NULL;
}
