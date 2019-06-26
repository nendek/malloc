/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:15:45 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:15:46 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_memcpy(void *src, void *dest, size_t nb)
{
	size_t	i;
	char	*str1;
	char	*str2;

	str1 = (char *)src;
	str2 = (char *)dest;
	i = 0;
	while (i < nb)
	{
		str2[i] = str1[i];
		i++;
	}
}

void	ft_bzero(void *ptr, size_t size)
{
	size_t			i;
	unsigned char	*zone;

	zone = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		zone[i] = 0;
		i++;
	}
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(size_t n)
{
	if (n < 10)
		ft_putchar((char)n + 48);
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
