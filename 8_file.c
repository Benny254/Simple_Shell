#include "main.h"

/**
 * new_node - add node to start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: list size
 */
list_t *new_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	bytemem((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = dupstr(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * node_add - add a node to the end of the list
 * @head: address of pointer to head node
 * @str: the str field of node
 * @num: the node index used by history
 * Return: the size of list
 */
list_t *node_add(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	bytemem((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = dupstr(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * str_print - print only the str element of a list_t linked list
 * @h: the pointer to first node
 * Return: size of list
 */
size_t str_print(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_str(h->str ? h->str : "(nil)");
		print_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_delete - delete node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 otherwise
 */
int node_delete(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

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
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * node_free - free all nodes of a list
 * @head_ptr: an address of pointer to head node
 * Return: void
 */
void node_free(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
