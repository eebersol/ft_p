/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 18:01:39 by eebersol         ###   ########.fr       */
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

# define S_GET "The file is download."
# define E_GET "The file is not download please retry."
# define F_SEND "Send failed."
# define F_RECV "Recv failed"
# define SUCCESS 1
# define ERROR -1
typedef	struct			s_server
{
	int 				socket;
	int 				sserver;
	char 				*racine;
	int 				puts;
	int 				file_fd;
}						t_server;

typedef	struct			s_client
{
	int 				socket;
	char 				*racine;
}						t_client;


// builtin_client.c //
void 		cd_client(char **cmd, char *path);
void 		pwd_client(char **cmd);
void		ls_client(char **cmd);
void 		client_quit(int socket);

// builtin_server.c //
void 		cd_server(char **cmd, int cs, char *path);
void 		pwd_server(int cs, char **cmd);
void		ls_server(int socket);

// client.c //
int			find_cmd_client(char **cmd, int sock, char *path);
void 		usage_client (char *str);
int 		create_client_ipv6(char *addr, int port);
int 		create_client(char *addr, int port);
void 		minishell(int socket, char *path);

//client_manage_file.c//
void 		put_file_client(char **arg, int socket);
void 		get_file_client(char **arg, int sock);

// init_client.c //
t_client	*recover_client(void);
t_client	*init_client(int sock);

// init_server.c //
t_server	*recover_server(void);
t_server	*init_server(int sock);

// server.c //
void 		server(int sock, char *path, int pid);
int 		find_cmd_server(char **cmd, int cs, char *path);
void		usage_server(char *str);
int 		accept_client_request(int socket);
int 		create_server(int port);

//server_reader.c//
void	 	get_file_server(int cs, char **cmd);
void 		put_file_server(int cs, char **cmd);
int 		reader(int cs, char *path);


// tools.c //
void 	client_quit(int socket);
void 	log_msg(char *str, int i);
void 	log_cd(int cs, int type, char *str, char *str2);
void 	log_put(int cs, int type, char *str, char *str2);
void 	log_get(int cs, int type, char *str, char *str2);
#endif