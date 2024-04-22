# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgonzal2 <pgonzal2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 19:35:55 by pgonzal2          #+#    #+#              #
#    Updated: 2024/04/22 12:02:50 by pgonzal2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
LIBFT_PATH = libft/libft.a

SRCS = main.c utils.c

CC = gcc -g
CFLAGS = -Wall -Werror -Wextra -g
OBJ = $(SRCS:.c=.o)
NAME = pipex
INCLUDES = -I . -I ${LIBFT_DIR}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(NAME): $(OBJ)
	@$(MAKE) -s all -C $(LIBFT_DIR)
	@$(CC) $(INCLUDES) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

clean: 
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ)
	
fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME) 

re: fclean all


.PHONY: all clean fclean re 