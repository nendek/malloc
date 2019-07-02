/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_protections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:58:00 by arobion           #+#    #+#             */
/*   Updated: 2019/07/01 15:10:55 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

int main() 
{ 
	void *addr; 

	if (!(addr = malloc(1 << 64)))
		write(1, "NULL1\n", 6);
	else
		write(1, "SUCCESS1\n", 9);

	if (!(addr = malloc(-1)))
		write(1, "NULL2\n", 6);
	else
		write(1, "SUCCESS2\n", 9);
	if (!(addr = malloc(SSIZE_MAX)))
		write(1, "NULL3\n", 6);
	else
		write(1, "SUCCESS3\n", 9);

	if (!(addr = malloc(SSIZE_MAX + 10000000)))
		write(1, "NULL4\n", 6);
	else
		write(1, "SUCCESS4\n", 9);
	
	if (!(addr = malloc(SSIZE_MAX - 40000000)))
		write(1, "NULL5\n", 6);
	else
		write(1, "SUCCESS5\n", 9);

	if (!(addr = malloc(SSIZE_MAX - 40)))
		write(1, "NULL6\n", 6);
	else
		write(1, "SUCCESS5\n", 9);
}
