# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amylle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 11:58:06 by amylle            #+#    #+#              #
#    Updated: 2024/02/27 14:42:07 by amylle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	= ./src
INC_DIR	= ./inc
OBJ_DIR	= ./obj

SRC	= ./src/main.c ./src/error.c ./src/hooks.c ./src/utils.c ./src/vector/vectortests.c ./src/vector/vector_utils1.c ./src/vector/vector_utils2.c \
	  ./src/parser/parser.c
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -g
INCLUDE	= -Llibft -lft -I$(INC_DIR) -Lmlx -lmlx_Linux -L/usr/lib -Imlx -lXext -lX11 -lm -lz
RM		= rm -rf
LIBFT	= libft/libft.a
MAKEFLAGS += --no-print-directory
MLX		= mlx/mlx_linux.a
NAME	= miniRT

#---------------------------Messages--------------------------------------------

BOLD_PURPLE	=	\033[1;35m

BOLD_CYAN	=	\033[1;36m

BOLD_YELLOW	=	\033[1;33m

NO_COLOR	=	\033[0m


all:	$(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Imlx -Iincludes -MJ $@.json -c $< -o $@ 

$(LIBFT):
		@make -C ./libft

$(MLX):
		@make -C ./mlx

$(NAME):	$(OBJS) $(LIBFT) $(MLX)
				@echo Compiling $(NAME)
				@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
				@echo "\033[33mMaking compile_commands.json...\033[0m"
				@find . -type f -name "compile_commands.json" -delete
				@find $(OBJ_DIR)/ -type f -name "*.json" | xargs sed -e '1s/^/[\n/' >> compile_commands.json
				@find ./libft/obj/libft/ -type f -name "*.json" | xargs sed -e '$$s/,$$/\n]/' >> compile_commands.json
				@find ./libft/obj/gnl/ -type f -name "*.json" | xargs sed -e '$$s/,$$/\n]/' >> compile_commands.json
				@find ./libft/obj/printf/ -type f -name "*.json" | xargs sed -e '$$s/,$$/\n]/' >> compile_commands.json
				@find $(OBJ_DIR)/ -type f -name "*.json" -delete
				@find ./libft/obj/libft/ -type f -name "*.json" -delete
				@find ./libft/obj/gnl/ -type f -name "*.json" -delete
				@find ./libft/obj/printf/ -type f -name "*.json" -delete

clean:	
				@echo "$(BOLD_YELLOW)Removing all object files and directories"
				$(RM) $(OBJ_DIR)
				@make clean -C ./libft

fclean:
				@echo "$(BOLD_YELLOW)Removing binaries"
				$(RM) $(NAME) $(OBJ_DIR)
				@make fclean -C ./libft
				@make clean -C ./mlx

test:		$(NAME)
				./$(NAME) test.rt

re:			fclean all
