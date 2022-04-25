# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 21:06:22 by eozben            #+#    #+#              #
#    Updated: 2022/04/25 05:21:27 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = init_valgrind
FLAGS = -Wall -Wextra -Werror
INC = setup_val.h
SRCS = init.c
OBJ_PATH = ./objs/
OBJS = $(patsubst %.c,$(OBJ_PATH)%.o,$(SRCS))
LIB = -Llibft -lft
LIBFT = ./libft/libft.a
UP = "\033[A"
CUT = "\033[K"

all:$(NAME) exec_valgrind

$(NAME): $(OBJ_PATH) $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIB)

exec_valgrind: exec.c
	@$(CC) $(FLAGS) exec.c -o exec_valgrind $(LIB)
	@echo "                                                         "
	@echo " \033[1;32m  ___|   _ \    \  |   _ \ _ _|  |      ____|  __ \   | "
	@echo "  |      |   |  |\/ |  |   |  |   |      __|    |   |  | "
	@echo "  |      |   |  |   |  ___/   |   |      |      |   | _| "
	@echo " \____| \___/  _|  _| _|    ___| _____| _____| ____/  _) \033[0m"
	@echo "                                                         "

$(OBJ_PATH)%.o: %.c $(INC)
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@echo ""
	@echo "libft:"
	@echo "\033[1;32m0%\033[0m   [                      ]"
	@sleep 0.1
	@printf $(UP)$(CUT)
	@echo "\033[1;32m33%\033[0m  [\033[1;32m ██████\033[0m               ]"
	@sleep 0.1
	@printf $(UP)$(CUT)
	@echo "\033[1;32m50%\033[0m  [\033[1;32m ██████████\033[0m           ]"
	@make -silent -C ./libft
	@printf $(UP)$(CUT)
	@echo "\033[1;32m83%\033[0m  [\033[1;32m ████████████████\033[0m     ]"
	@sleep 0.1
	@printf $(UP)$(CUT)
	@echo "\033[1;32m100%\033[0m [\033[1;32m ████████████████████ \033[0m]"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C ./libft
	@echo "\033[1;32m.o files removed!\033[0m"

fclean:
	@rm -rf $(NAME)
	@rm -rf exec_valgrind
	@rm -rf $(OBJ_PATH)
	@make fclean -C ./libft
	@echo "\033[1;32mbinary files removed!\033[0m"

re: fclean all