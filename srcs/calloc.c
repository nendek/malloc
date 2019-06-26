/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:15:14 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:15:15 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*calloc(size_t nitems, size_t size)
{
	size_t	true_size;
	void	*ret;

	if (!check_limits(size))
		return (NULL);
	true_size = nitems * size;
	if (!check_limits(true_size))
		return (NULL);
	ret = malloc(true_size);
	if (true_size <= SMALL)
		ft_bzero(ret, malloc_good_size(true_size - sizeof(t_chunk)));
	else
		ft_bzero(ret, malloc_good_size(true_size));
	return (ret);
}
