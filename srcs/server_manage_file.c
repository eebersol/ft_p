/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_manage_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 16:34:18 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"


void 	server_put_file(char **arg)
{
	int 	fd;
	// int 	r;
	
	if ((fd = open(arg[7], O_CREAT|O_WRONLY, 0777)) == -1)
		printf("Error open.\n");
	printf("%s\n", arg[5]);
	if (write(fd, arg[5], atoi(arg[3])) == -1)
		printf("Error write.\n");
	return ;
}	