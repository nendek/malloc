/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:15:01 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:15:02 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		update_size_free(t_chunk *current,
		char depth, char side, size_t zone_size)
{
	if (side == LEFT)
	{
		if (current->left->size_left > current->left->size_right)
			current->size_left = current->left->size_left;
		else if (current->left->size_left < current->left->size_right)
			current->size_left = current->left->size_right;
		else if (current->left->size_left == (zone_size / (1 << (depth + 1))))
			current->size_left = (uint32_t)(zone_size / (1 << depth));
		else
			current->size_left = current->left->size_left;
	}
	else
	{
		if (current->right->size_left > current->right->size_right)
			current->size_right = current->right->size_left;
		else if (current->right->size_left < current->right->size_right)
			current->size_right = current->right->size_right;
		else if (current->right->size_left == (zone_size / (1 << (depth + 1))))
			current->size_right = (uint32_t)(zone_size / (1 << depth));
		else
			current->size_right = current->right->size_left;
	}
}

void		deallocate_handler(t_chunk *current, void *to_free,
		char depth, size_t zone_size)
{
	if ((void*)current == to_free)
	{
		current->size_right = (uint32_t)(zone_size / (1 << depth));
		current->right = NULL;
	}
	else if ((size_t)to_free == (size_t)current - (zone_size / (1 << depth)))
	{
		current->size_left = (uint32_t)(zone_size / (1 << depth));
		current->left = NULL;
	}
}

void		set_size(t_chunk *current, size_t zone_size, char depth, char side)
{
	if (side == LEFT)
	{
		current->size_left = (uint32_t)(zone_size / (1 << depth));
		current->left = NULL;
	}
	else
	{
		current->size_right = (uint32_t)(zone_size / (1 << depth));
		current->right = NULL;
	}
}

void		deallocate(t_chunk *current, void *to_free,
		char depth, size_t zone_size)
{
	if (depth < MAX_DEPTH)
	{
		if (current->left && current->left != current
				&& (size_t)current > (size_t)to_free)
		{
			deallocate(current->left, to_free, depth + 1, zone_size);
			update_size_free(current, depth, LEFT, zone_size);
		}
		else if (current->right && current->right != current
				&& ((size_t)current <= (size_t)to_free))
		{
			deallocate(current->right, to_free, depth + 1, zone_size);
			update_size_free(current, depth, RIGHT, zone_size);
		}
		else if (current->left == current->right)
			deallocate_handler(current, to_free, depth, zone_size);
		else if (current->left == current && ((size_t)to_free
					== (size_t)current - (zone_size / (1 << depth))))
			set_size(current, zone_size, depth, LEFT);
		else if (current->right == current
				&& (size_t)current == (size_t)to_free)
			set_size(current, zone_size, depth, RIGHT);
	}
}

t_chunk		*launch_deallocate(t_header *head, void *ptr, size_t size)
{
	t_chunk		*chunk;

	chunk = (t_chunk *)((size_t)head + (size / 2));
	deallocate(chunk,
				(void *)((size_t)ptr - sizeof(t_chunk)), 1, size);
	return (chunk);
}
