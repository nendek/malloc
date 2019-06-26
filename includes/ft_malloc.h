/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnardozi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:14:39 by pnardozi          #+#    #+#             */
/*   Updated: 2019/06/26 14:14:42 by pnardozi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TINY 992
# define TINY_ZONE 2 * 1024 * 1024
# define MAX_DEPTH 16
# define SMALL 127 * 1024 - 1
# define SMALL_ZONE 16 * 1024 * 1024

# define LEFT 1
# define RIGHT 2
# define FREE 0
# define SPLIT 1
# define FULL 2

typedef struct			s_header
{
	size_t				available_mem;
	struct s_header		*next;
	size_t				nb_allocs;
	size_t				type;
}						t_header;

typedef struct			s_chunk
{
	struct s_chunk		*left;
	struct s_chunk		*right;

	uint32_t			size_left;
	uint32_t			size_right;
	struct s_chunk		*previous;

}						t_chunk;

typedef struct			s_control
{
	size_t				total_mem;
	t_header			*head;
	char				reserved[4080];
}						t_control;

extern	t_control *g_control;
extern	pthread_mutex_t g_mutex;

/*
 **	malloc functions
*/
void					*malloc(size_t size);
void					*lock_malloc(size_t size);
t_control				*init(void);
void					*get_alloc(size_t size, size_t zone_size);
void					*alloc_large(size_t size);
void					*get_zone(size_t size, size_t zone_type,
		size_t zone_size);
void					*init_zone(size_t zone_size);
void					*get_chunk(void *zone, size_t size, size_t zone_size);
void					*allocate(t_chunk *current, char depth,
		size_t size, size_t zone_size);
void					*new_allocate(t_chunk *current, char depth,
		size_t zone_size);
t_chunk					*new_node(t_chunk *current, char depth,
		char side, size_t zone_size);
void					update_size_allocation(t_chunk *current, char side);

/*
 ** realloc functions
*/
void					*realloc(void *ptr, size_t size);
void					*lock_realloc(void *ptr, size_t size);
size_t					get_alloc_size(t_chunk *current, void *to_find,
		char depth, size_t zone_size);
size_t					get_alloc_size_handler(t_chunk *current,
		size_t to_find, char depth, size_t size);
size_t					get_full_size(t_header *head, void *ptr);
void					ft_memcpy(void *src, void *dest, size_t nb);

/*
 ** calloc functions
*/
void					*calloc(size_t nitems, size_t size);
void					ft_bzero(void *ptr, size_t size);

/*
 **	free functions
*/
void					free(void *ptr);
void					lock_free(void *ptr);
t_header				*find_zone(void *ptr);
size_t					get_end_zone(size_t dep, t_header *head);
void					deallocate(t_chunk *current, void *to_free, char depth,
		size_t zone_size);
void					deallocate_handler(t_chunk *current, void *to_free,
		char depth, size_t zone_size);
t_chunk					*launch_deallocate(t_header *head,
		void *ptr, size_t size);
void					set_size(t_chunk *current,
		size_t zone_size, char depth, char side);
void					free_large(t_header *head);
void					update_size_free(t_chunk *current, char depth,
		char side, size_t zone_size);
void					handle_unmap(t_header *head);

/*
 **	other functions
*/
size_t					malloc_good_size(size_t size);
size_t					malloc_size(void *ptr);
size_t					lock_malloc_size(void *ptr);
int						check_limits(size_t size);

/*
 **	display functions
*/
void					show_alloc_mem(void);
void					lock_show_alloc_mem(void);
void					ft_putstr(char *str);
void					ft_putchar(char c);
void					ft_putnbr(size_t nb);
void					ft_puthexa(size_t n);
void					print_hexa(size_t nb);
char					conv_tab(size_t nb);
void					print_allocs_zone(t_chunk *current, char depth,
		size_t zone_size, size_t *total);
size_t					print_zone(t_header *header);
void					write_zone(size_t current,
		size_t zone_size, char depth, char side);
void					show_zone(void);
void					show_large_zone(t_header *header, size_t *total);

#endif
