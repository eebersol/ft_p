/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:40:30 by eebersol         ###   ########.fr       */
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

# define CLT "client"
# define SRV "server"

#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define RESET "\x1B[0m"

/* builtin_client */
int			cd_client_response(int flag);
int			cd_client(char **cmd, char *path);
int			pwd_client(char **cmd);
int			ls_client(char **cmd);
void		client_quit(int socket);
/* builtin_server */
void		cd_server_response(int cs, int flag);
void		cd_server(char **cmd, int cs, char *path);
void		pwd_server(int cs, char **cmd);
void		ls_server(int socket);
/* client */
void		usage_client (char *str);
int			create_client_ipv6(char *addr, int port);
int			find_cmd_client(char *buf, int sock, char *path);
void		minishell(int socket, char *path);
/* shared_function */
int			cd_move_back(char *old_pwd, char *path);
int			command_validity(char *side, char **cmd);
/* server */
int			reader(int cs, char *path);
int			create_server_ipv6(int port);
void		server(int sock, char *path, int pid);
int			find_cmd_server(char **cmd, int cs, char *path);
/* get_client */
int			get_server_response(int cs, char **cmd);
int			get_open_client(char *name);
int			get_client(char **cmd, int cs);
/* get_server */
int 		get_open_server(int cs, char *name);
void		get_server(int cs, char **cmd);
/* put_client */
int			put_server_response(int cs, char *name);
int			put_open_client(char *name);
int			put_client(char **cmd, int cs);
/* put_server */
int			put_open_server(char *name, int cs);
void		put_server(int cs, char **cmd);

#endif