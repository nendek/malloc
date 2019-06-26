# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arobion <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/11 17:36:04 by arobion           #+#    #+#              #
#    Updated: 2019/06/26 14:11:00 by arobion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Weverything

ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
	endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so
FILES = malloc.c free.c malloc_good_size.c show_alloc_mem.c \
		realloc.c calloc.c limits.c libutils.c show_utils.c \
		allocate.c deallocate.c zone_utils.c

SRCS_DIR = srcs
SRCS = $(addprefix $(SRCS_DIR)/,$(FILES))

INCS_DIR = includes
INCS = -I $(INCS_DIR)

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/,$(FILES:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
		$(CC) $(CFLAGS) $(INCS) -o $(NAME) -shared $(OBJS)
			ln -sf $(NAME) $(LINK)

$(OBJS_DIR):
		mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		$(CC) $(CFLAGS) -fPIC $(INCS) -c -o $@ $<

clean:
		rm -rf objs

fclean: clean
		rm -f $(NAME) $(LINK)

re: fclean all

.PHONY: all clean fclean re

