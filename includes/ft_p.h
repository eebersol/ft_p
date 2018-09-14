/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 16:41:28 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P
# define FT_P

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <string.h>

typedef	struct			s_env
{
	int 				socket;
	char 				*racine;
}						t_env;

// client.c //
void 		usage_client (char *str);
int 		create_client(char *addr, int port);
// server.c //
void		exec_ls(char **cmd, int socket);
void 		find_cmd(char *buf, char **cmd, int socket);
void		usage_server(char *str);
int 		create_server(int port);
// cd.c //

void 		cd(char **cmd);
void 		pwd(void);
// init.c //
t_env		*recover_env(void);
t_env		*init_env(void);

//client_manage_file.c//
char 	*put_file(char **arg);
//server_manage_file.c//
void 	server_put_file(char **arg);
#endif