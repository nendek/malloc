/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:22 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:16:25 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t	get_alloc_size_handler(t_chunk *current, size_t to_find,
		char depth, size_t size)
{
	if (current->left && current->left != current && (size_t)current > to_find)
		return (get_alloc_size(current->left, (void*)to_find, depth + 1, size));
	else if (current->right && current->right != current
			&& ((size_t)current <= to_find))
		return (get_alloc_size(current->right,
					(void*)to_find, depth + 1, size));
	else if (current->left == current->right)
	{
		if ((size_t)current == to_find)
			return ((uint32_t)(size / (1 << (depth - 0))));
		else if (to_find == (size_t)current - (size / (1 << depth)))
			return ((uint32_t)(size / (1 << (depth - 0))));
		else
			return (0);
	}
	else if (current->left == current
			&& (to_find == (size_t)current - (size / (1 << depth))))
		return ((uint32_t)(size / (1 << (depth - 0))));
	else if (current->right == current && (size_t)current == to_find)
		return ((uint32_t)(size / (1 << (depth - 0))));
	else
		return (0);
}

size_t	get_alloc_size(t_chunk *current,
		void *to_find, char depth, size_t zone_size)
{
	if (!(current))
		return (0);
	if (depth < MAX_DEPTH)
		return (get_alloc_size_handler(current,
					(size_t)to_find, depth, zone_size));
	else
		return (0);
}

size_t	get_full_size(t_header *head, void *ptr)
{
	t_chunk	*chunk;

	if (head->type == TINY)
	{
		chunk = (t_chunk *)((size_t)head + (TINY_ZONE / 2));
		return (get_alloc_size(chunk,
				(void *)((size_t)ptr - sizeof(t_chunk)), 1, TINY_ZONE));
	}
	else if (head->type == SMALL)
	{
		chunk = (t_chunk *)((size_t)head + (SMALL_ZONE / 2));
		return (get_alloc_size(chunk,
				(void *)((size_t)ptr - sizeof(t_chunk)), 1, SMALL_ZONE));
	}
	else
		return (head->type);
}

void	*lock_realloc(void *ptr, size_t size)
{
	t_header	*head;
	size_t		full_size;
	void		*ret;

	if (!g_control)
		return (NULL);
	if (!check_limits(size))
		return (NULL);
	if (!(ptr))
		return (lock_malloc(size));
	if ((head = find_zone(ptr)) == NULL)
		return (NULL);
	size = malloc_good_size(size);
	full_size = get_full_size(head, ptr);
	if (full_size == 0)
		return (NULL);
	if (full_size >= size)
		return (ptr);
	ret = lock_malloc(size);
	ft_memcpy(ptr, ret, full_size);
	lock_free(ptr);
	return (ret);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_mutex);
	ret = lock_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
