/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 16:41:24 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void usage_client (char *str)
{
	printf("uage: %s  <addr> <port>\n", str);
	exit(-1);
}

int 	create_client(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Connect error\n");
		exit(2);
	}
	return (sock);
}

int main(int ac, char **av)
{
	int 				port;
	int					sock;
	char 				*buf;
	char 				server_reply[1024];
	char 				**arg;

	if (ac != 3)
		usage_client(av[0]);
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	while (42)
    {
    	ft_putstr("> : ");
		while (ft_get_next_line(0, &buf))
		{
			//Send some data
			arg = ft_strsplit(buf, ' ');
			if (ft_strcmp(arg[0], "quit") == 0)
			{
				close(sock);
				exit(0);
			}
			if (ft_strcmp(arg[0], "put") == 0)
			{
				buf = put_file(arg);
			}
			else if (send(sock, buf, strlen(buf), 0) < 0)
			{
				ft_putstr("Send failed");
				return (1);
			}
			//Receive a reply from the server
			if (recv(sock, server_reply, 1024, 0) < 0)
			{
				ft_putstr("[client]: recv failed");
				break;
			}
			ft_putstr(server_reply);
			ft_putstr("> : ");
			bzero(&server_reply, 1024);
		}
	}
	close(sock);
}