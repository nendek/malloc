/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:14:50 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:14:51 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_chunk		*new_node(t_chunk *current, char depth, char side, size_t zone_size)
{
	t_chunk		*ret;
	uint32_t	diff;

	diff = (uint32_t)(zone_size / (1 << depth));
	if (side == LEFT)
		ret = (t_chunk *)((size_t)current - diff);
	else
		ret = (t_chunk *)((size_t)current + diff);
	ret->left = NULL;
	ret->right = NULL;
	ret->size_left = diff;
	ret->size_right = diff;
	ret->previous = current;
	return (ret);
}

void		update_size_allocation(t_chunk *current, char side)
{
	if (side == LEFT)
	{
		if (current->left->size_left >= current->left->size_right)
			current->size_left = current->left->size_left;
		else
			current->size_left = current->left->size_right;
		if (!(current->left->left))
			current->left = current;
	}
	else
	{
		if (current->right->size_left >= current->right->size_right)
			current->size_right = current->right->size_left;
		else
			current->size_right = current->right->size_right;
		if (!(current->right->right))
			current->right = current;
	}
}

void		*new_allocate(t_chunk *current, char depth, size_t zone_size)
{
	current->size_left = 0;
	current->size_right = 0;
	current->left = NULL;
	current->right = NULL;
	return ((void *)((size_t)current
				- (zone_size / (1 << depth)) + sizeof(t_chunk)));
}

void		*allocate(t_chunk *current, char depth,
		size_t size, size_t zone_size)
{
	void	*ret;

	if (depth < MAX_DEPTH)
	{
		if (!(current->left))
			current->left = new_node(current, depth + 1, LEFT, zone_size);
		if (!(current->right))
			current->right = new_node(current, depth + 1, RIGHT, zone_size);
		if (current->size_left >= size)
		{
			ret = allocate(current->left, depth + 1, size, zone_size);
			update_size_allocation(current, LEFT);
			return (ret);
		}
		else if (current->size_right >= size)
		{
			ret = allocate(current->right, depth + 1, size, zone_size);
			update_size_allocation(current, RIGHT);
			return (ret);
		}
		else
			return (new_allocate(current, depth, zone_size));
	}
	else
		return (new_allocate(current, depth, zone_size));
}
