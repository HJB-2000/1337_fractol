/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:49:11 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 02:27:15 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_garbage	*new_node(void *ptr, int i)
{
	t_garbage	*new;

	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->_malloc = ptr;
	new->index = i;
	new->next = NULL;
	return (new);
}

void	add_node(t_garbage **head, t_garbage *new_node)
{
	t_garbage	*tmp;

	if (!*head)
	{
		(*head) = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	_free(t_garbage **list)
{
	t_garbage	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->_malloc);
		tmp->_malloc = NULL;
		free(tmp);
		tmp = NULL;
	}
	*list = NULL;
}

void	*treat_ptr(size_t size, void *ptr)
{
	void	*instant;

	instant = NULL;
	if (!ptr && size > 0)
	{
		instant = malloc(size);
		if (!instant)
			return (NULL);
	}
	else if (ptr)
		instant = ptr;
	return (instant);
}

void	*_malloc(size_t size, void *ptr, bool free_flag, bool error_flag)
{
	static t_garbage	*head = NULL;
	t_garbage			*new;
	static int			i = 0;
	void				*instant;

	if (free_flag)
		return (_free(&head), NULL);
	instant = treat_ptr(size, ptr);
	if (!instant)
		error_flag = true;
	if (error_flag)
	{
		_free(&head);
		perror("we faced a problem");
		atexit(l);
		exit(EXIT_FAILURE);
	}
	new = new_node(instant, i);
	i++;
	if (!new)
	{
		_free(&head);
		return (free(instant), NULL);
	}
	add_node(&head, new);
	return (instant);
}
