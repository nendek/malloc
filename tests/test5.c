/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_show.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:45:29 by arobion           #+#    #+#             */
/*   Updated: 2019/07/01 15:05:31 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_malloc.h"

int main() 
{ 
	void *ptr;

	ptr = malloc(992); 
	ptr = malloc(1024); 
	ptr = malloc(1024 * 32); 
	ptr = malloc(1024 * 1024); 
	ptr = malloc(1024 * 1024 * 16); 
	ptr = malloc(1024 * 1024 * 128); 
	show_alloc_mem(); 
	return (0); 
} 
