NAME			=	minishell

SRC_DIR			=	./source_files
SRC				=	$(SRC_DIR)/main.c \
					$(SRC_DIR)/split.c \
					$(SRC_DIR)/preparsing.c

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
	@$(CC) $(OBJ) $(CFLAGS) $(LFLAGS) -o $(NAME)

clean			:
	@rm -rf $(OBJ_DIR)/*.o

fclean			:	clean
	@rm -rf $(NAME)

re				:	fclean all