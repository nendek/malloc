/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_protections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:58:00 by arobion           #+#    #+#             */
/*   Updated: 2019/06/25 17:09:01 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
}
