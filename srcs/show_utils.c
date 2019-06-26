/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:16:44 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:16:45 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

char	conv_tab(size_t nb)
{
	return ((char)nb + (nb < 10 ? '0' : 55));
}

void	ft_puthexa(size_t n)
{
	if (n < 16)
		ft_putchar(conv_tab(n));
	else
	{
		ft_puthexa(n / 16);
		ft_puthexa(n % 16);
	}
}

void	print_hexa(size_t nb)
{
	write(1, "0x", 2);
	ft_puthexa(nb);
}

void	write_zone(size_t current, size_t zone_size, char depth, char side)
{
	if (side == 2)
		print_hexa(current + sizeof(t_chunk));
	else
		print_hexa(current - (zone_size / (1 << (depth))) + sizeof(t_chunk));
	write(1, " - ", 3);
	if (side == 1)
		print_hexa(current);
	else
		print_hexa(current + (zone_size / (1 << (depth))));
	write(1, " : ", 3);
	if (side == 3)
		ft_putnbr((zone_size / (1 << (depth - 1)) - sizeof(t_chunk)));
	else
		ft_putnbr((zone_size / (1 << (depth)) - sizeof(t_chunk)));
	ft_putstr(" octets\n");
}
