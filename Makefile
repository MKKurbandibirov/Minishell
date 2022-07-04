NAME		=	minishell

CC			=	gcc

# FLAGS		=	-Wall -Wextra -Werror -g

FLAGS		=	-Wall -Wextra -g
INCL		= 	./header_files/

CFLAGS		=	$(FLAGS) -lreadline -I $(INCL)

PATH_SRC	=	source_files/

PATH_PARS	=	$(PATH_SRC)parser/

PATH_BUIL	=	$(PATH_SRC)builtins/

PATH_EXE	=	$(PATH_SRC)execute/

PATH_LFT	=	libft/

PATH_OBJ	=	./object_files/

FILE_SRC	=	main.c \
				signal.c prompt.c star.c

FILE_PRS	=	parser.c \
				prevalidator.c  utils.c prepars_list_func.c preparsing.c quote.c utils1.c\
				utils.c slave.c slaveLST.c master.c get_cmd_plist.c utils2.c validator.c

FILE_BUIL	=	cd.c\
				echo_n.c env.c exit.c export_utils1.c export.c pwd.c unset.c cd_utils.c utils.c

FILE_EXE	=	execute.c \
				find_cmd.c redirects.c execute_utils.c heredoc.c help_pars_here.c 
				
LIBFT_SRC	=	ft_atoi.c		ft_bzero.c		ft_calloc.c	ft_isalnum.c	ft_isalpha.c	ft_isascii.c	ft_isdigit.c	ft_isprint.c\
				ft_itoa.c		ft_memchr.c	ft_memcmp.c 	ft_memcpy.c 	ft_memmove.c 	ft_memset.c	ft_putchar_fd.c	ft_strjoin_free.c\
				ft_putendl_fd.c ft_putnbr_fd.c 	ft_putstr_fd.c 	ft_split.c 		ft_strchr.c 	ft_strcmp.c		ft_strdup.c		ft_striteri.c\
				ft_strjoin.c 	ft_strlcat.c 	ft_strlcpy.c 	ft_strlen.c 	ft_strmapi.c 	ft_strncmp.c	ft_strnstr.c\
				ft_strrchr.c 	ft_strtrim.c 	ft_substr.c 	ft_tolower.c 	ft_toupper.c 	ft_isspace.c	ft_strncpy.c\
				ft_lstadd_back_bonus.c 			ft_lstadd_front_bonus.c 		ft_lstclear_bonus.c			ft_lstdelone_bonus.c				ft_lstiter_bonus.c\
				ft_lstlast_bonus.c				ft_lstnew_bonus.c				ft_lstsize_bonus.c				ft_lstmap_bonus.c

HEAD_FILE	=	./header_files/minishell.h\
				./header_files/builtins.h\
				./header_files/execute.h\
				./header_files/parser.h\
				./libft/libft.h

SRC_SH		=	$(addprefix $(PATH_SRC), $(FILE_SRC))\
				$(addprefix $(PATH_PARS), $(FILE_PRS))\
				$(addprefix $(PATH_BUIL), $(FILE_BUIL))\
				$(addprefix $(PATH_EXE), $(FILE_EXE))

SRC_FT		=	$(addprefix $(PATH_LFT), $(LIBFT_SRC))

OBJ			=	$(patsubst $(PATH_SRC)%, $(PATH_OBJ)%, $(SRC_SH:.c=.o))


#****************************************************************************************************************************************************************************#

.PHONY			:	all clean fclean re
.ONESHELL		:

all				:	$(NAME) $(HEAD_FILE)

$(PATH_OBJ)%.o	:	$(PATH_SRC)%.c $(HEAD_FILE)
	@if ! [ -d ./object_files ] ; then \
		mkdir object_files ; \
		mkdir object_files/parser ; \
		mkdir object_files/builtins ; \
		mkdir object_files/execute ; \
	fi 
	@$(CC) $(FLAGS) -c $< -o $@
	@echo FILE COLLECTED $@

$(NAME)			:	 $(OBJ) $(HEAD_FILE) $(SRC_FT) $(SRC_SH)
	@make -C libft/
	@$(CC) $(CFLAGS) $(PATH_OBJ)*.o $(PATH_OBJ)builtins/*.o $(PATH_OBJ)parser/*.o $(PATH_OBJ)execute/*.o -o $(NAME)

clean			:
	@rm -rf $(PATH_OBJ)

fclean			:	clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re				:	fclean all
