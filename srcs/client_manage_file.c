/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 16:18:03 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"



void 	put_file_client(char **arg, int socket)
{
	char 	buf[1024];
	int 	fd;
	int 	r;
	char	 *str;
	;
	if (!arg[1])
		printf("[client] ERROR : put need argument\n");
	else if (arg[2])
		printf("[client] ERROR : put to many argument\n");
	else if ((fd = open(arg[1], 0)) == -1)
		printf("[client] ERROR : open %s fail\n", arg[1]);
	else
	{
		str = ft_strjoin(arg[0], " ");
		str = ft_strjoin(str, arg[1]);
		send(socket, str, ft_strlen(str), 0);
		while ((r = read(fd, &buf, 1023)) > 0)
		{
			send(socket, buf, r, 0);
			ft_bzero(&buf, 1024);
		}
		close(fd);
		printf("[client] SUCCES : %s was sent\n", arg[1]);
	}
}


void 	get_file_client(char **arg, int sock)
{
	int 	fd;
	int 	r;
	char 	buf[1024];
	
	if (!arg[1])
		printf("[client] ERROR : get need argument\n");
	else if (arg[2])
		printf("[client] ERROR : get to many argument\n");
	else if ((fd = open(arg[1], 0)) == -1)
		printf("[client] ERROR : open %s fail\n", arg[1]);
	else
	{
		while ((r = read(sock, buf, 1023)) > 0)
		{
			buf[r] = '\0';
			write(fd, buf, 1023);
			if (r < 1023)
				break;
			bzero(&buf, 1024);
		}
		close(fd);
		printf("[client] SUCCES : %s has been received\n", arg[1]);
	}
	return ;
}