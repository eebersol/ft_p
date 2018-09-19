/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 18:03:22 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>

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

int 	create_server_ipv6(int port)
{
	int 				sock;
	struct protoent 	*proto;
	struct sockaddr_in6 	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port 	= htons(port);
	sin.sin6_addr 	= in6addr_any;
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 42);
	return (sock);
}


int accept_client_request(int sock)
{
	struct sockaddr_in 	*csin;
	unsigned int 		cslen;
	int 				cs;

	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	if (cs < 0)
		usage_server("fork(1)");
	return (cs);
}

void 	server(int sock, char *path, int pid)
{
	struct sockaddr_in 	*csin;
	unsigned int 		cslen;
	int 				cs;
	int 				r;

	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	if ((pid = fork()) == 0)
	{
		r = reader(cs, path);
		if (r == 0)
			ft_putstr("Client disconnect.");
		if (r == -1)
			ft_putstr("[server]Recv fail.");
		close(cs);
		exit(0);
	}
}
int main(int ac, char **av)
{
	char 				path[2048];
	int					sock;
	int 				pid;

	pid = 0;
	ac != 2 ? usage_server(av[0]) : 0;
	sock = create_server_ipv6(atoi(av[1]));
	getcwd(path, 2048);
	while (1)
		server(sock, path, pid);
}