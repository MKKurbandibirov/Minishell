NAME			=	minishell

SRCDIR			=	source_files

SRC				=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/echo_n.c $(SRC_DIR)/pwd.c 			$(SRC_DIR)/cd.c 	$(SRC_DIR)/env.c \
					$(SRC_DIR)/export.c	$(SRC_DIR)/export_utils.c	$(SRC_DIR)/unset.c 	$(SRC_DIR)/exit.c \
					$(SRC_DIR)/find_cmd.c \
					$(SRC_DIR)/parser/pars_list_func.c	$(SRC_DIR)/parser/parser.c		$(SRC_DIR)/parser/parsing_continue.c \
					$(SRC_DIR)/parser/parsing.c 		$(SRC_DIR)/parser/quotes.c	$(SRC_DIR)/parser/validators.c
					

OBJDIR			=	object_files
OBJ				=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
LFLAGS			=	-lreadline

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)			:	$(OBJ)
	@make -C libft/
	@$(CC) $(OBJDIR)/*.o $(OBJDIR)/parser/*.o $(CFLAGS) $(LFLAGS) -o $(NAME)

clean			:
	@rm -rf $(OBJDIR)/*.o $(OBJDIR)/parser/*.o

fclean			:	clean
	@rm -rf $(NAME)

re				:	fclean all