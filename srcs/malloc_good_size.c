/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_good_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:12 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 18:10:56 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		malloc_good_size(size_t size)
{
	if (size <= TINY)
		size = (((size - 1) >> 4) << 4) + 16 + sizeof(t_chunk);
	else if (size <= SMALL)
		size = (((size - 1) >> 9) << 9) + 512 + sizeof(t_chunk);
	else
		size = (((size - 1) >> 12) << 12) + 4096;
	return (size);
}

size_t		lock_malloc_size(void *ptr)
{
	t_header	*head;
	t_chunk		*chunk;

	if (!g_control)
		return (0);
	if (!(ptr))
		return (0);
	if ((head = find_zone(ptr)) == NULL)
		return (0);
	if (head->type == TINY)
	{
		chunk = (t_chunk *)((size_t)head + (TINY_ZONE / 2));
		return (get_alloc_size(chunk, (void *)((size_t)ptr - sizeof(t_chunk)),
					1, TINY_ZONE) - sizeof(t_chunk));
	}
	else if (head->type == SMALL)
	{
		chunk = (t_chunk *)((size_t)head + (SMALL_ZONE / 2));
		return (get_alloc_size(chunk, (void *)((size_t)ptr - sizeof(t_chunk)),
					1, TINY_ZONE) - sizeof(t_chunk));
	}
	else
		return (head->type);
}

size_t		malloc_size(void *ptr)
{
	size_t ret;

	pthread_mutex_lock(&g_mutex);
	ret = lock_malloc_size(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
