/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/17 17:21:45 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

void		exec_ls(char **cmd, int socket)
{
	pid_t	pid;
	int		flag;
	int 	status;

	flag = 0;
	dup2(socket, 1);
	dup2(socket, 2);
	if ((pid = fork()) == 0)
	{
		if ((execve("/bin/ls", cmd, NULL)) != -1)
			flag = -1;
		flag = 1;
	}
	wait4(pid, &status, -1, NULL);
	return ;
}

void	find_cmd(char **cmd, int socket)
{	
	
	if (ft_strcmp(cmd[1], "ls") == 0)
		exec_ls(cmd, socket);
	else if (ft_strcmp(cmd[1], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd[1], "pwd") == 0)
		pwd();
	else
		write(recover_env()->socket, "Command not found.\n", 19); 
}


void usage_server(char *str)
{
	printf("usage: %s <port>\n", str);
	exit(-1);
}

int 	create_server(int port)
{
	int 				sock;
	struct protoent 	*proto;
	struct sockaddr_in 	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family 		= AF_INET;
	sin.sin_port 		= htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 42);
	return (sock);
}

int main(int ac, char **av)
{
	t_env 				*env;
	int 				port;
	int					sock;
	int 				cs;
	unsigned int 		cslen;
	struct sockaddr_in 	*csin;
	int 				r;
	int 				pid;
	char 				buf[1024];
	char 				**cmd;

	pid = 0;
	cmd = NULL;
	if (ac != 2)
		usage_server(av[0]);
	env = init_env();
	port = atoi(av[1]);
	sock = create_server(port);
	while (1)
	{
		//Receive a reply from the server
		cs = accept(sock, (struct sockaddr*)&csin, &cslen);
		if (cs < 0)
			usage_server("fork(1)");
		// if ((pid = fork()) < 0)
		// 	usage_server("fork(2)");
		if ((pid = fork()) == 0)
		{
			env->socket = cs;
			while((r = read(cs, &buf, 1023)) > 0)
			{
				//printf("ici\n");
				buf[r] = '\0';
				cmd = ft_strsplit(buf, ':');
				if (ft_strcmp(cmd[1], "put") != 0)
				{
					find_cmd(cmd, cs);
				}
				else
				{
					server_put_file(cmd, cs);
					write(cs, "\n", 1);
				}
			//	printf(" la %s\n", buf);
				ft_bzero(&buf, 1023);
			}
			if (r == 0)
				ft_putstr("Client disconnect.");
			if (r == -1)
				ft_putstr("[server]Recv fail.");
			close(cs);
			exit(0);
		}
	}
}