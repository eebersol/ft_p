/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/17 17:33:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"



void 	put_file(char **arg, int socket)
{
	char 	*pathfile;
	char 	buf[1024];
	int 	fd;
	int 	r;
	int 	len;
	char 	*res;
	
	pathfile = arg[1];
	res = malloc(1);
	len = 0;
	if ((fd = open(pathfile, 0)) == -1)
		printf("Error open.\n");
	if ((r = read(fd, &buf, 2048)) == -1)
		printf("Error read.\n");
	while ((r = read(fd, &buf, 1023)) > 0)
		len += r;
	close(fd);
	ft_bzero(&buf, 1024);
	res = ft_strjoin("cmd:", arg[0]);
	res = ft_strjoin(res, ":name:");
	res = ft_strjoin(res, arg[1]);
	res = ft_strjoin(res, ":len:");
	res = ft_strjoin(res, ft_itoa(len));
	res = ft_strjoin(res, "\0");
	//printf("res : %s\n", res);
	if (send(socket, res, ft_strlen(res), 0) < 0)
		ft_putstr("Send failed");
	if ((fd = open(pathfile, 0)) == -1)
		printf("Error open.\n");
	while ((r = read(fd, &buf, 1023)) > 0)
	{
		send(socket, buf, r, 0);
		ft_bzero(&buf, 1024);
	}
	return ;
}