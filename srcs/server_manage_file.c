/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/18 16:27:02 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void 	server_put_file(char **arg, int socket)
{
	int 	fd;
	int 	r;
	int 	len;
	char 	buf[1024];
	
	len = 0;
	ft_bzero(&buf, 1024);
	if ((fd = open(arg[1], O_CREAT|O_WRONLY, 0777)) == -1)
		printf("Error open.\n");
	printf("server_put_file 1\n");
	while ((r = read(socket, &buf, 1023)) > 0)
	{
		printf("server_put_file 2\n");
		buf[r] = '\0';
		printf("buf : %s\n", buf);
		write(fd, buf, r);
		ft_bzero(&buf, 1024);
	}
	printf("server_put_file 3\n");
	return ;
}	
