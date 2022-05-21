NAME			=	minishell

SRCDIR			=	source_files
SRC				=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/find_cmd.c $(SRC_DIR)/execute.c \
					$(SRC_DIR)/signal.c \
					$(SRC_DIR)/builtins/echo_n.c	$(SRC_DIR)/builtins/pwd.c 			$(SRC_DIR)/builtins/cd.c 			$(SRC_DIR)/builtins/env.c \
					$(SRC_DIR)/builtins/export.c	$(SRC_DIR)/builtins/export_utils1.c $(SRC_DIR)/builtins/export_utils2.c	$(SRC_DIR)/builtins/unset.c 	$(SRC_DIR)/builtins/exit.c \
					$(SRC_DIR)/parser/pars_list_func.c	$(SRC_DIR)/parser/parser.c		$(SRC_DIR)/parser/parsing_continue.c \
					$(SRC_DIR)/parser/parsing.c 		$(SRC_DIR)/parser/quotes.c		$(SRC_DIR)/parser/validators.c
					

OBJDIR			=	object_files
OBJ				=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
LFLAGS			=	-lreadline

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJDIR)		:
	@mkdir object_files
	@mkdir object_files/parser
	@mkdir object_files/builtins

$(NAME)			:	$(OBJ)
	@make -C libft/
	@$(CC) $(OBJDIR)/*.o $(OBJDIR)/builtins/*.o $(OBJDIR)/parser/*.o $(CFLAGS) $(LFLAGS) -o $(NAME)

clean			:
	@rm -rf $(OBJDIR)/*.o $(OBJDIR)/builtins/*.o $(OBJDIR)/parser/*.o

fclean			:	clean
	@make fclean -C libft/
	@rm -rf $(NAME)
	@rm -rf object_files
	@rm -rf object_files/parser
	@rm -rf object_files/builtins

re				:	fclean all