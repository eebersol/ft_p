/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/18 17:03:07 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"



void 	put_file(char **arg, int socket)
{
	char 	buf[1024];
	int 	fd;
	int 	r;
	char	 *str;
	
	str = ft_strjoin(arg[0], " ");
	str = ft_strjoin(str, arg[1]);
	send(socket, str, ft_strlen(str), 0);
	if ((fd = open(arg[1], 0)) == -1)
		printf("Error open.\n");	printf("1 - %s\n", str);
	while ((r = read(fd, &buf, 1023)) > 0)
	{
		printf("Enter\n");
		send(socket, buf, r, 0);
		ft_bzero(&buf, 1024);
	}
	printf("Je sors\n");
	return ;
}