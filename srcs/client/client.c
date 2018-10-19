/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:41:25 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int		find_cmd_client(char *buf, int sock, char *path)
{
	char	**arg;

	if (!buf[0])
		return (0);
	else
		arg = ft_strsplit(buf, ' ');
	if (ft_strcmp(arg[0], "quit") == 0)
		client_quit(sock);
	else if (ft_strcmp(arg[0], "lcd") == 0)
		return (cd_client(arg, path));
	else if (ft_strcmp(arg[0], "lpwd") == 0)
		return (pwd_client(arg));
	else if (ft_strcmp(arg[0], "lls") == 0)
		return (ls_client(arg));
	else if (ft_strcmp(arg[0], "get") == 0)
		return (get_client(arg, sock));
	else if (ft_strcmp(arg[0], "put") == 0)
		return (put_client(arg, sock));
	else
		return (1);
	return (0);
}

void	minishell(int sock, char *path)
{
	char	*buf;
	char	server_reply[1024];
	char	**arg;
	int		r;

	r = 0;
	while (ft_get_next_line(0, &buf))
	{
		arg = ft_strsplit(buf, ' ');
		if (find_cmd_client(buf, sock, path))
		{
			buf = ft_strjoin(buf, "\n");
			if (send(sock, buf, ft_strlen(buf), 0) < 0)
				printf(RED"client - error send fail."RESET"\n");
			else if ((r = read(sock, server_reply, 1024)) < 0)
				printf(RED"cient - error read fail."RESET"\n");
			server_reply[r] = '\0';
			ft_putstr(server_reply);
		}
		ft_putstr("> : ");
		ft_bzero(&server_reply, 1024);
	}
	return ;
}

int		create_client_ipv6(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = PF_INET6;
	inet_pton(PF_INET6, addr, &sin.sin6_addr);
	sin.sin6_port = htons(port);
	connect(sock, (const struct sockaddr *)&sin, sizeof(sin));
	return (sock);
}

int		main(int ac, char **av)
{
	char	path[2048];
	int		sock;

	if (ac != 3)
		printf(RED"client - error : invalid number argument."RESET"\n");
	else
	{
		sock = create_client_ipv6(av[1], atoi(av[2]));
		getcwd(path, 2048);
		while (42)
		{
			ft_putstr("> : ");
			minishell(sock, path);
		}
		close(sock);
	}
	return (0);
}
