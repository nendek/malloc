/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:15:53 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 19:48:32 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		check_limits(size_t size)
{
	struct rlimit r_limit;

	if (getrlimit(RLIMIT_AS, &r_limit))
		return (0);
	if (size >= r_limit.rlim_max)
		return (0);
	size = malloc_good_size(size);
	if (size + (size_t)getpagesize() >= r_limit.rlim_max)
		return (0);
	return (1);
}
