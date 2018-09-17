/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/17 17:10:16 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void 	server_put_file(char **arg, int socket)
{
	int 	fd;
	int 	r;
	int 	len;
	char 	buf[1024];
	
	(void)socket;
	(void)arg;
	len = 0;
	if ((fd = open(arg[3], O_CREAT|O_WRONLY, 0777)) == -1)
		printf("Error open.\n");
	while ((r = read(socket, &buf, 1023)) > 0)
	{
		buf[r] = '\0';
		write(fd, buf, r);
		ft_bzero(&buf, 1024);
	}
	return ;
}	
