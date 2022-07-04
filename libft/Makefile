# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfarfetc <nfarfetc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 19:12:18 by nfarfetc          #+#    #+#              #
#    Updated: 2022/07/04 17:07:49 by nfarfetc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRC			=	ft_atoi.c 		ft_bzero.c 		ft_calloc.c 	ft_isalnum.c 	ft_isalpha.c 	ft_isascii.c 	ft_isdigit.c 	ft_isprint.c \
				ft_itoa.c 		ft_memchr.c 	ft_memcmp.c 	ft_memcpy.c 	ft_memmove.c 	ft_memset.c 	ft_putchar_fd.c ft_strjoin_free.c \
				ft_putendl_fd.c ft_putnbr_fd.c 	ft_putstr_fd.c 	ft_split.c 		ft_strchr.c 	ft_strcmp.c		ft_strdup.c 	ft_striteri.c \
				ft_strjoin.c 	ft_strlcat.c 	ft_strlcpy.c 	ft_strlen.c 	ft_strmapi.c 	ft_strncmp.c 	ft_strnstr.c \
				ft_strrchr.c 	ft_strtrim.c 	ft_substr.c 	ft_tolower.c 	ft_toupper.c 	ft_isspace.c	ft_strncpy.c\
				ft_lstadd_back_bonus.c 	ft_lstadd_front_bonus.c 	ft_lstclear_bonus.c 	ft_lstdelone_bonus.c 	ft_lstiter_bonus.c \
				ft_lstlast_bonus.c 		ft_lstnew_bonus.c 			ft_lstsize_bonus.c 		ft_lstmap_bonus.c		get_next_line.c		gnl_join.c

HEADER		=	libft.h

OBJ_DIR		=	../object_files
OBJ 		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

.PHONY		:	all fclean

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(HEADER)
	@ar rcs $(NAME) $?

$(OBJ_DIR)/%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo FILE COLLECTED $@

fclean 		:
	@rm -rf $(NAME)
