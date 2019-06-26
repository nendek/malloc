/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:15:23 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 19:33:44 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		handle_unmap(t_header *head)
{
	t_header *tmp;

	if (head->nb_allocs == 0)
	{
		if (g_control->head == head)
			return ;
		else
		{
			tmp = g_control->head;
			while (tmp->next != head)
				tmp = tmp->next;
			tmp->next = head->next;
		}
		if (head->type == TINY)
			munmap((void *)head, TINY_ZONE);
		else if (head->type == SMALL)
			munmap((void *)head, SMALL_ZONE);
		else
			munmap((void *)head, head->type);
	}
	if (g_control->head == NULL)
	{
		munmap((void *)g_control, (size_t)getpagesize());
		g_control = NULL;
	}
}

void		free_large(t_header *head)
{
	t_header *tmp;

	tmp = g_control->head;
	if (tmp == head)
	{
		munmap((void *)head, head->type + (size_t)getpagesize());
		g_control->head = NULL;
		return ;
	}
	while (tmp->next != head)
		tmp = tmp->next;
	tmp->next = head->next;
	munmap((void *)head, head->type + (size_t)getpagesize());
}

void		lock_free(void *ptr)
{
	t_header	*head;
	t_chunk		*chunk;

	if (!g_control)
		return ;
	chunk = NULL;
	if ((head = find_zone(ptr)) == NULL)
		return ;
	if (head->type == TINY)
		chunk = launch_deallocate(head, ptr, TINY_ZONE);
	else if (head->type == SMALL)
		chunk = launch_deallocate(head, ptr, SMALL_ZONE);
	else
	{
		free_large(head);
		return ;
	}
	if (chunk->size_left > chunk->size_right)
		head->available_mem = (size_t)(chunk->size_left);
	else
		head->available_mem = (size_t)(chunk->size_right);
	(head->nb_allocs)--;
	handle_unmap(head);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	lock_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}
