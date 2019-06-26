/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:39:15 by arobion           #+#    #+#             */
/*   Updated: 2019/06/25 15:53:55 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	show_zone(void)
{
	char	*zone;

	zone = (char *)g_control->head;
	int i = 0;
	while (i < TINY_ZONE)
	{
		if (zone[i] == -1)
			write(1, "X", 1);
		else
			write(1, "o", 1);
		i++;
	}

}

// int main(void)
// {
// 	size_t i = 0;
// 	(void)i;
// 	char *str;
// 	(void)str;
//  	size_t size_alloc = TINY;
// 	(void)size_alloc;
// 	size_t	j;
// 	(void)j;
// 
// 	
// // 	str = malloc(500);
// // 	char *str3 = malloc(500);
// // 	str3 = malloc(500);
// // 	str = malloc(500);
// // 	// test pointeur pas a nous
// // 	char str2[] = "test";
// // 	free(str2);
// // 	// test mauvaise addresse
// // 	show_alloc_mem();
// // 	free(&(str[1]));
// // 	show_alloc_mem();
// 	str = malloc(500);
// 	dprintf(1, "1er show_alloc, 1 zone de 992\n");
// 	show_alloc_mem();
// 	free((void *)str);
// 	size_t		tab[255];
//    	while (i < 255)
//   	{
//   		str = (char *)malloc(450);
//  		j = 0;
//   		while (j < 450)
//   		{
//   			str[j] = -1;
//   			j++;
//   		}
// 		free(str);
// 		tab[i] = (size_t)str;
//   		i++;
//   	}
// 	i = 0;
// 	while (i < 255)
// 	{
// 		free((void *)(tab[i]));
// 		i++;
// 	}
// 	dprintf(1, "\n2eme show alloc, 0 zone\n");
// 	show_alloc_mem();
// 	str = malloc(500);
// 	dprintf(1, "\n3eme show alloc, normalement 1 zone de 992\n");
// 	show_alloc_mem();
// 	free((void *)str);
// 	dprintf(1, "\n4eme show alloc : plus rien\n");
// 	show_alloc_mem();
// 	str = malloc(1500);
// 	dprintf(1, "\n5eme show alloc : 1 TINY et 1 SMALL\n");
// 	show_alloc_mem();
// 	free((void *)str);
// 	dprintf(1, "\n6eme show alloc : SMALL a disparu\n");
// 	show_alloc_mem();
// 	str = malloc(10);
// 	str = realloc(str, 16);
// 
// 
// 	return (0);
// }


// TEST 0 13 L
// int main(void)
// { 
// 	int i; 
// 	char *addr; 
// 	(void)addr;
// 
// 	i = 0; 
// 	while (i < 1024) 
// 	{ 
// 		i++; 
// 	} 
// 	return (0); 
// } 


// TEST 1 15 L
// int main(void) 
// { 
// 	int i; 
// 	char *addr; 
// 
// 	i = 0; 
// 	while (i < 10000) 
// 	{ 
// 		addr = (char*)malloc(1024); 
// 		addr[0] = 42; 
// 		i++; 
// 	} 
// 	show_alloc_mem();
// 	return (0); 
// } 

// TEST 2 15L
int main(void) 
{ 
	int i; 
	char *addr; 

	i = 0;
	show_alloc_mem();
	while (i < 1) 
	{ 
		addr = (char*)malloc(1024); 
		addr[0] = 42; 
 		free(addr); 
		i++; 
	} 
	return (0); 
} 

// TEST 3 21L
// #include <string.h>
// #define M (1024 * 1024) 
// 
// void print(char *s) 
// { 
// 	write(1, s, strlen(s)); 
// } 
// 
// int main() 
// { 
// 	char *addr1; 
// 	char *addr3; 
// 
// 	addr1 = (char*)malloc(16*M); 
// 	strcpy(addr1, "Bonjours\n"); 
// 	print(addr1); 
// 	addr3 = (char*)realloc(addr1, 128*M); 
// 	addr3[127*M] = 42; 
// 	print(addr3); 
// 	return (0); 
// } 
