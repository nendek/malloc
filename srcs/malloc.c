/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:02 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:16:03 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_control *g_control = NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_control	*init(void)
{
	t_control *control;

	control = (t_control *)mmap(0, sizeof(t_control),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	control->total_mem = sizeof(t_control);
	control->head = NULL;
	return (control);
}

void		*get_chunk(void *zone, size_t size, size_t zone_size)
{
	t_chunk		*chunk;

	chunk = (t_chunk *)((size_t)zone + (zone_size / 2));
	chunk = allocate(chunk, 1, size, zone_size);
	return ((void *)chunk);
}

void		*get_alloc(size_t size, size_t zone_size)
{
	void		*zone;
	t_header	*head;
	t_chunk		*chunk;

	size = malloc_good_size(size);
	if (zone_size == TINY_ZONE)
		zone = get_zone(size, TINY, TINY_ZONE);
	else if (zone_size == SMALL_ZONE)
		zone = get_zone(size, SMALL, SMALL_ZONE);
	else
		zone = get_zone(size, size, size);
	if (!zone)
		return (NULL);
	head = (t_header *)zone;
	chunk = (t_chunk *)((size_t)zone + (zone_size / 2));
	zone = get_chunk(zone, size, zone_size);
	if (chunk->size_left > chunk->size_right)
		head->available_mem = (size_t)(chunk->size_left);
	else
		head->available_mem = (size_t)(chunk->size_right);
	(head->nb_allocs)++;
	return (zone);
}

void		*lock_malloc(size_t size)
{
	if (!check_limits(size))
		return (NULL);
	if (!g_control)
		g_control = init();
	if (size <= TINY)
		return (get_alloc(size, TINY_ZONE));
	else if (size <= SMALL)
		return (get_alloc(size, SMALL_ZONE));
	else
		return (alloc_large(size));
}

void		*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = lock_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
