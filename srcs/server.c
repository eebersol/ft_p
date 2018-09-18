/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/18 17:30:33 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

void		exec_ls(int socket)
{
	pid_t	pid;
	int		flag;
	char 	*cmd[2];
	int 	status;

	flag = 0;
	cmd[0] = "/bin/ls";
	cmd[1] = NULL;
	dup2(socket, 1);
	dup2(socket, 2);
	if ((pid = fork()) == 0)
	{
		execve(cmd[0], cmd, NULL);
	}
	wait4(pid, &status, -1, NULL);
	close(1);
	close(2);
	return ;
}

void	find_cmd(char **cmd, int socket)
{	
	if (ft_strcmp(cmd[0], "ls") == 0)
		exec_ls(socket);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
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

	pid = 0;
	if (ac != 2)
		usage_server(av[0]);
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
			env = init_env();
			env->sserver = sock;
			env->socket = cs;
			printf("MAIN\n");
			r = reader(cs);
			// while((r = read(cs, &buf, 1023)) > 0)
			// {
			// 	buf[r] = '\0';
			// 	cmd = ft_strsplit(buf, ' ');
			// 	printf("Name : %s %s %s\n", cmd[0], cmd[1], cmd[2]);
			// 	if (ft_strcmp(cmd[0], "put") == 0)
			// 	{
			// 		printf("Enter\n");
			// 		server_put_file(cmd, cs);
			// 		//write(cs, "\n", 1);
			// 	}
			// 	else
			// 	{
			// 		find_cmd(cmd, cs);
			// 	}
			// 	ft_bzero(&buf, 1024);
			// }
			if (r == 0)
				ft_putstr("Client disconnect.");
			if (r == -1)
				ft_putstr("[server]Recv fail.");
			close(cs);
			exit(0);
		}
	}
}