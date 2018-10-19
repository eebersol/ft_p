/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:33:57 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

int			find_cmd_server(char **cmd, int cs, char *path)
{
	if (ft_strcmp(cmd[0], "ls") == 0)
		ls_server(cs);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_server(cmd, cs, path);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_server(cs, cmd);
	else if (ft_strcmp(cmd[0], "put") == 0)
		put_server(cs, cmd);
	else if (ft_strcmp(cmd[0], "get") == 0)
		get_server(cs, cmd);
	else
		write(cs, "server ERROR : Command not found.\n", 36);
	return (0);
}

int			reader(int cs, char *path)
{
	char	buf[1024];
	char	**cmd;
	int		r;

	cmd = NULL;
	while ((r = read(cs, &buf, 1023)) > 0)
	{
		buf[r - 1] = ' ';
		buf[r] = '\0';
		cmd = ft_strsplit(buf, '\n');
		cmd = ft_strsplit(buf, ' ');
		find_cmd_server(cmd, cs, path);
		ft_bzero(&buf, 1024);
	}
	return (r);
}

void		run_server(int sock, char *path, int pid)
{
	struct sockaddr_in	*csin;
	unsigned int		cslen;
	int					cs;
	int					r;

	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	if ((pid = fork()) == 0)
	{
		r = reader(cs, path);
		if (r == 0)
			printf(YEL "server : info : Client disconnect"RESET"\n");
		if (r == -1)
			printf(RED"server : error : Read client socket fail."RESET"\n");
		close(cs);
		exit(0);
	}
}

int			create_server_ipv6(int port)
{
	struct protoent		*proto;
	struct sockaddr_in6	sin;
	int					sock;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 42);
	return (sock);
}

int			main(int ac, char **av)
{
	char	path[2048];
	int		sock;
	int		pid;

	pid = 0;
	if (ac == 2)
	{
		sock = create_server_ipv6(atoi(av[1]));
		getcwd(path, 2048);
		while (1)
			run_server(sock, path, pid);
	}
	else
	{
		printf(RED"server - error : invalid number argument."RESET"\n");
		exit(-1);
	}
	return (0);
}
