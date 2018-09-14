/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 16:41:19 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"



char 	*put_file(char **arg)
{
	char 	*pathfile;
	char 	buf[2048];
	int 	fd;
	int 	r;
	char 	*res;
	
	pathfile = arg[1];
	res = malloc(1);
	if ((fd = open(pathfile, 0)) == -1)
		printf("Error open.\n");
	if ((r = read(fd, &buf, 2048)) == -1)
		printf("Error read.\n");
	else
	{
		buf[r] = '\0';
		res = ft_strjoin(res, "cmd:put:len:");
		res = ft_strjoin(res, ft_itoa(ft_strlen(buf)));
		res = ft_strjoin(res, ":content:");
		res = ft_strjoin(res, buf);
		res = ft_strjoin(res, ":name:");
		res = ft_strjoin(res, pathfile);
		return (res);
	}
	return (NULL);
}	