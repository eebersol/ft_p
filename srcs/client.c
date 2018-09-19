/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 17:42:19 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void usage_client (char *str)
{
	printf("uage: %s  <addr> <port>\n", str);
	exit(-1);
}

int 	create_client_ipv6(char *addr, int port)
{
	int 				sock;
	struct protoent 	*proto;
	struct sockaddr_in6 	sin;

	(void)port;
	if (inet_pton(PF_INET6, addr, &sin.sin6_addr) == false)
		printf(" 1 : Connect error Ipv6\n");
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);;
	sin.sin6_family 		= PF_INET6;
	inet_pton(PF_INET6, addr, &sin.sin6_addr);
	sin.sin6_port 		= htons(port);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Connect error Ipv6\n");
		exit(2);
	}
	return (sock);
}

int 	create_client(char *addr, int port)
{
	int 				sock;
	struct protoent 	*proto;
	struct sockaddr_in 	sin;

	if (inet_addr(addr) == INADDR_NONE)
	{
		return (create_client_ipv6(addr, port));
	}
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);;
	sin.sin_family 		= PF_INET;
	sin.sin_port 		= htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Connect error Ipv4\n");
		exit(2);
	}
	return (sock);
}

int	find_cmd_client(char **arg, int sock, char *path)
{	
	if (ft_strcmp(arg[0], "quit") == 0)
		client_quit(sock);
	else if (ft_strcmp(arg[0], "put") == 0)
		put_file_client(arg, sock);
	else if (ft_strcmp(arg[0], "lcd") == 0)
		cd_client(arg, path);
	else if (ft_strcmp(arg[0], "lpwd") == 0)
		pwd_client(arg);
	else if (ft_strcmp(arg[0], "lls") == 0)
		ls_client(arg);
	else
		return (0);
	return (1);
}

void 	minishell(int sock, char *path)
{
	char 	*buf;
	char 	server_reply[1024];
	char 	**arg;
	int 	r;

	ft_putstr("> : ");
	r =  0;
	while (ft_get_next_line(0, &buf))
	{
		arg = ft_strsplit(buf, ' ');
		if (find_cmd_client(arg, sock, path) == 0) 
		{
			if (send(sock, buf, ft_strlen(buf), 0) < 0)
				log_msg(F_SEND, 3);
			if (ft_strcmp(arg[0],"get") == 0)
				get_file_client(arg, sock);
			else if ((r = read(sock, server_reply, 1024)) < 0)
				log_msg(F_RECV, 3);
			server_reply[r] = '\0';
			ft_putstr(server_reply);
		}
		ft_putstr("> : ");
		bzero(&server_reply, 1024);
	}
	return ;
}

int main(int ac, char **av)
{
	char 				path[2048];
	int					sock;

	if (ac != 3)
		usage_client(av[0]);
	sock = create_client(av[1], atoi(av[2]));
	getcwd(path, 2048);
	while (42)
 		minishell(sock, path);
	close(sock);
	return (0);
}