/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:52 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:16:53 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		get_end_zone(size_t dep, t_header *head)
{
	if (head->type == TINY)
		return (dep + TINY_ZONE);
	else if (head->type == SMALL)
		return (dep + SMALL_ZONE);
	else
		return (dep + head->type);
}

t_header	*find_zone(void *ptr)
{
	t_header	*tmp;
	size_t		dep;
	size_t		end;

	tmp = (t_header*)(g_control->head);
	dep = (size_t)tmp;
	end = get_end_zone(dep, tmp);
	while ((size_t)ptr < dep || (size_t)ptr > end)
	{
		tmp = tmp->next;
		if (!tmp)
			return (NULL);
		dep = (size_t)tmp;
		end = get_end_zone(dep, tmp);
	}
	return (tmp);
}

void		*init_zone(size_t zone_size)
{
	void		*ret;
	t_header	*tmp;
	t_chunk		*chunk;

	if (!(ret = mmap(0, zone_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	chunk = (t_chunk *)((size_t)ret + (zone_size / 2));
	chunk->left = NULL;
	chunk->right = NULL;
	chunk->size_left = (uint32_t)(zone_size / 2);
	chunk->size_right = (uint32_t)(zone_size / 2);
	get_chunk(ret, sizeof(t_chunk), zone_size);
	tmp = (t_header *)ret;
	tmp->available_mem = zone_size / 2;
	tmp->next = NULL;
	if (zone_size == TINY_ZONE)
		tmp->type = TINY;
	else if (zone_size == SMALL_ZONE)
		tmp->type = SMALL;
	else
		tmp->type = zone_size;
	tmp->nb_allocs = 0;
	return (ret);
}

void		*get_zone(size_t size, size_t zone_type, size_t zone_size)
{
	void		*ret;
	t_header	*head;
	t_header	*tmp;

	tmp = NULL;
	if (g_control->head == 0)
	{
		ret = init_zone(zone_size);
		g_control->head = (t_header *)ret;
		return (ret);
	}
	head = (g_control->head);
	while (head && (head->available_mem < size || head->type != zone_type))
	{
		tmp = head;
		head = head->next;
	}
	if (!head)
	{
		ret = init_zone(zone_size);
		tmp->next = ret;
		return (ret);
	}
	return ((void *)head);
}

void		*alloc_large(size_t size)
{
	t_header	*header;
	t_header	*tmp;
	void		*zone;

	tmp = NULL;
	size = malloc_good_size(size) + 4096;
	header = g_control->head;
	while (header)
	{
		tmp = header;
		header = header->next;
	}
	if (!(zone = mmap(0, size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	header = (t_header *)zone;
	header->next = NULL;
	header->available_mem = 0;
	header->nb_allocs = 1;
	header->type = size - 4096;
	if (!(g_control->head))
		g_control->head = header;
	else
		tmp->next = header;
	return ((void *)((size_t)zone + sizeof(t_header)));
}
