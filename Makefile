NAME			=	minishell

SRC_DIR			=	./source_files
SRC				=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/echo_n.c $(SRC_DIR)/pwd.c $(SRC_DIR)/cd.c $(SRC_DIR)/env.c $(SRC_DIR)/export.c\
					$(SRC_DIR)/export_utils.c

OBJ_DIR			=	./object_files
OBJ 			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
LFLAGS			=	-lreadline

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)			:	$(OBJ)
	@make -C libft/
	@$(CC) $(OBJ_DIR)/*.o $(CFLAGS) $(LFLAGS) -o $(NAME)

clean			:
	@rm -rf $(OBJ_DIR)/*.o

fclean			:	clean
	@rm -rf $(NAME)

re				:	fclean all