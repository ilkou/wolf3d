# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/24 18:58:22 by oouklich          #+#    #+#              #
#    Updated: 2019/12/24 20:29:24 by oouklich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = main.c\
      map.c\
      draw_lodev.c\
      load_texture.c\
      keys.c

SRCS = $(addprefix srcs/w3d_, $(SRC))
SRCS += srcs/print_map.c
OBJS = $(SRC:%.c=objs/w3d_%.o)
OBJS += objs/print_map.o
OBJS_DIR = objs

ifeq ($(shell uname), Darwin)
MLX_DIR = minilibx_macos
MLX = -lmlx -framework OpenGL -framework AppKit
else
MLX_DIR = minilibx_linux
MLX = -lm -lmlx -lXext -lX11
endif

LIBFT = -lft
LIBFT_DIR = libft

THREAD = -lpthread

INC = inc

COMPILER = gcc #-Werror -Wextra -Wall

GREEN_COLOR=\x1b[32;01m
NO_COLOR=\x1b[0m
BUILD_PRINT = $(GREEN_COLOR)wolf3d successfully compiles$(NO_COLOR)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	@$(COMPILER) -o $@ $(OBJS) -L $(MLX_DIR) $(MLX) -I $(MLX_DIR) -L $(LIBFT_DIR) $(LIBFT) $(THREAD) -I $(LIBFT_DIR) -I $(INC) && echo "$(BUILD_PRINT)"

$(OBJS_DIR):
	@mkdir -p $@

objs/%.o: srcs/%.c inc/wolf3d.h
	@$(COMPILER) -c $< -o $@ -I $(MLX_DIR) -I $(INC) -I $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	@rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
