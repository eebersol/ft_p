# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/08 19:11:03 by eebersol          #+#    #+#              #
#    Updated: 2018/09/14 15:55:53 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the program

NAME_SERVER		= server

NAME_CLIENT		= client

LIB				=	./libft/libft.a

_SRC_C			= client.c\
					client_manage_file.c\

_SRC_S			= server.c\
					builtin.c\
					init.c\
					server_manage_file.c\

INCLUDES		= -I./libft/includes/ -I./includes/

SRC_C			= $(addprefix srcs/,$(_SRC_C))
SRC_S			= $(addprefix srcs/,$(_SRC_S))

OBJ_C			= $(SRC_C:.c=.o)
OBJ_S			= $(SRC_S:.c=.o)

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME) $(NAME_OTOOL)

$(NAME_SERVER): $(OBJ_S) 
	@make -C ./libft/
	@gcc $(CFLAGS) -lm -L libft/ -lft $(OBJ_S) $(LIB) $(INCLUDES) -o $(NAME_SERVER)
	@echo $(NAME_SERVER) " : compiled"

$(NAME_CLIENT): $(OBJ_C) 
	@make -C ./libft/
	@gcc $(CFLAGS) -lm -L libft/ -lft $(OBJ_C) $(LIB) $(INCLUDES) -o $(NAME_CLIENT)
	@echo $(NAME_CLIENT) " : compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -f $(OBJ_S)
	@rm -f $(OBJ_C)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME_SERVER)
	@/bin/rm -rf $(NAME_CLIENT)
	@echo "Clean all .o and .a"

re: fclean all

.PHONY: clean fclean re