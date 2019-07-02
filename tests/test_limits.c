/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_limits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:11:24 by arobion           #+#    #+#             */
/*   Updated: 2019/07/01 15:27:13 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	size_t	i = 0;
	size_t	size2 = 0;
	void	*addr;
	size_t	checkpoint = 1000000;

	while (size < SSIZE_MAX)
	{
		if (!(addr = malloc(size)))
		{
			write(1, "NULL\n", 5);
			break ;
		}
		size += 1000000;
		if (size % checkpoint == 0)
		{
			dprintf(1, "size = %lu\n", size);
			checkpoint *= 10;
		}
	}
	dprintf(1, "size = %lu\n", size);
}
