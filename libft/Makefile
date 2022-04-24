# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 21:06:22 by eozben            #+#    #+#              #
#    Updated: 2022/04/24 18:49:37 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c \
	ft_strcmp.c ft_tolower.c ft_get_next_line.c ft_get_next_line_utils.c

OBJ_PATH = ./objs/
OBJS = $(patsubst %.c,$(OBJ_PATH)%.o,$(SRC))

all:$(NAME)

$(NAME): $(OBJ_PATH) $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

$(OBJ_PATH)%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)

fclean:
	@rm -rf $(NAME)
	@rm -rf $(OBJ_PATH)

re: fclean all