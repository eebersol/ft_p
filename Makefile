# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/08 19:11:03 by eebersol          #+#    #+#              #
#    Updated: 2018/09/27 16:59:15 by eebersol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Define the program

NAME_SERVER		= server

NAME_CLIENT		= client

LIB				= ./libft/libft.a

INCLUDES		= -I./libft/includes/ -I./includes/

CFLAGS			= -Wall -Wextra -Werror

_SRC_C			= client.c\
					builtin_client.c\
					put_client.c\
					get_client.c\

_SRC_S			= server.c\
					builtin_server.c\
					put_server.c\
					get_server.c\

_SRC_SHARE		= shared_function.c\

SRC_C			= $(addprefix srcs/client/,$(_SRC_C))
SRC_S			= $(addprefix srcs/server/,$(_SRC_S))
SRC_SHARE		= $(addprefix srcs/shared/,$(_SRC_SHARE))

OBJ_C			= $(SRC_C:.c=.o)
OBJ_S			= $(SRC_S:.c=.o)
OBJ_SHARE		= $(SRC_SHARE:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_S) $(OBJ_SHARE)
	@make -C ./libft/
	@gcc $(CFLAGS) -lm -L libft/ -lft  $(OBJ_S) $(OBJ_SHARE) $(LIB) $(INCLUDES) -o $(NAME_SERVER)
	@echo $(NAME_SERVER) " : compiled"

$(NAME_CLIENT): $(OBJ_C) $(OBJ_SHARE)
	@make -C ./libft/
	@gcc $(CFLAGS) -lm -L libft/ $(OBJ_C) $(OBJ_SHARE) $(LIB) $(INCLUDES) -o $(NAME_CLIENT)
	@echo $(NAME_CLIENT) " : compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -f $(OBJ_S)
	@rm -f $(OBJ_C)
	@rm -f $(OBJ_SHARE)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME_SERVER)
	@/bin/rm -rf $(NAME_CLIENT)
	@echo "Clean all .o and .a"

re: fclean all



.PHONY: clean fclean re