/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:35 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:16:36 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_allocs_zone(t_chunk *current,
		char depth, size_t zone_size, size_t *total)
{
	if (depth < MAX_DEPTH)
	{
		if (current->left && current->left != current)
			print_allocs_zone(current->left, depth + 1, zone_size, total);
		if (current->right && current->right != current)
			print_allocs_zone(current->right, depth + 1, zone_size, total);
		if (current->left == current)
		{
			write_zone((size_t)current, zone_size, depth, 1);
			*total += (zone_size / (1 << (depth)) - sizeof(t_chunk));
		}
		if (current->right == current)
		{
			write_zone((size_t)current, zone_size, depth, 2);
			*total += (zone_size / (1 << (depth)) - sizeof(t_chunk));
		}
	}
	else
	{
		if (current->size_left == 0 && current->size_right == 0)
		{
			write_zone((size_t)current, zone_size, depth, 3);
			*total += (zone_size / (1 << (depth)) - sizeof(t_chunk));
		}
	}
}

void	show_large_zone(t_header *header, size_t *total)
{
	ft_putstr("LARGE : ");
	print_hexa((size_t)header);
	write(1, "\n", 1);
	print_hexa((size_t)header + sizeof(t_header));
	write(1, " - ", 3);
	print_hexa((size_t)header + header->type);
	write(1, " : ", 3);
	ft_putnbr(header->type - sizeof(t_chunk));
	*total += header->type - sizeof(t_chunk);
	ft_putstr(" octets\n");
}

size_t	print_zone(t_header *header)
{
	t_chunk	*chunk;
	size_t	total;

	total = 0;
	chunk = NULL;
	if (header->type == TINY)
	{
		ft_putstr("TINY : ");
		chunk = (t_chunk*)((size_t)header + TINY_ZONE / 2);
		print_hexa((size_t)header);
		write(1, "\n", 1);
		print_allocs_zone(chunk, 1, TINY_ZONE, &total);
	}
	else if (header->type == SMALL)
	{
		ft_putstr("SMALL : ");
		chunk = (t_chunk*)((size_t)header + SMALL_ZONE / 2);
		print_hexa((size_t)header);
		write(1, "\n", 1);
		print_allocs_zone(chunk, 1, SMALL_ZONE, &total);
	}
	else
		show_large_zone(header, &total);
	return (total);
}

void	lock_show_alloc_mem(void)
{
	t_header	*header;
	size_t		total;

	total = 0;
	if (!g_control)
	{
		ft_putstr("rien\n");
		return ;
	}
	header = g_control->head;
	while (header)
	{
		total += print_zone(header);
		header = header->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	lock_show_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
}
