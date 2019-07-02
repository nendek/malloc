/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:24:05 by arobion           #+#    #+#             */
/*   Updated: 2019/07/01 15:09:03 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

int main(void)
{
	size_t i = 0;
	char *str;
 	size_t size_alloc = TINY;
	size_t	j;

	str = malloc(TINY);
	dprintf(1, "1er show_alloc, 1 zone de 992 + header\n");
	show_alloc_mem();
	free(str);
	size_t		tab[255];
   	while (i < 255)
  	{
  		str = (char *)malloc(450);
 		j = 0;
  		while (j < 450)
  		{
  			str[j] = -1;
  			j++;
  		}
// 		free(str);
		tab[i] = (size_t)str;
  		i++;
  	}
	dprintf(1, "\n2eme show alloc, tout est alloue sur 480 octets + header\n");
	show_alloc_mem();
	i = 0;
	while (i < 255)
	{
		free((void *)(tab[i]));
		i++;
	}
	dprintf(1, "\n3eme show alloc, que le header\n");
	show_alloc_mem();
	str = malloc(500);
	dprintf(1, "\n4eme show alloc, 1 zone de 992 + header\n");
	show_alloc_mem();
	free((void *)str);
	dprintf(1, "\n5eme show alloc : que le header \n");
	show_alloc_mem();
	str = malloc(1500);
	dprintf(1, "\n6eme show alloc : 1 TINY vide et 1 SMALL avec une zone de 2016\n");
	show_alloc_mem();
	free((void *)str);
	dprintf(1, "\n7eme show alloc : 1 TINY avec que le header\n");
	show_alloc_mem();
	return (0);
}

