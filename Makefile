NAME			=	minishell

SRCDIR			=	source_files
SRC				=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/builtins/echo_n.c	$(SRC_DIR)/builtins/pwd.c 			$(SRC_DIR)/builtins/cd.c 			$(SRC_DIR)/builtins/env.c \
					$(SRC_DIR)/builtins/export.c	$(SRC_DIR)/builtins/export_utils1.c $(SRC_DIR)/builtins/export_utils2.c	$(SRC_DIR)/builtins/unset.c 	$(SRC_DIR)/builtins/exit.c \
					$(SRC_DIR)/find_cmd.c $(SRC_DIR)/execute.c \
					$(SRC_DIR)/signal.c
					

OBJDIR			=	object_files
OBJ 			=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

CC				=	gcc -g -O2
CFLAGS			=	-Wall -Wextra -Werror
LFLAGS			=	-lreadline

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(OBJDIR)/%.o	:	$(SRCDIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)			:	$(OBJ)
	@make -C libft/
	@$(CC) $(OBJDIR)/*.o $(OBJDIR)/builtins/*.o  $(CFLAGS) $(LFLAGS) -o $(NAME)

clean			:
	@rm -rf $(OBJDIR)/*.o $(OBJDIR)/builtins/*.o 

fclean			:	clean
	@rm -rf $(NAME)

re				:	fclean all