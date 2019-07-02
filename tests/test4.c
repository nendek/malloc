/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_erreures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:43:49 by arobion           #+#    #+#             */
/*   Updated: 2019/06/25 16:44:21 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 

int main() 
{ 
	char *addr; 

	addr = malloc(16); 
	free(NULL); 
	free((void *)addr + 5); 
	if (realloc((void *)addr + 5, 10) == NULL) 
		print("Bonjours\n"); 
} 
