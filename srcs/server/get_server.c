/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:30:00 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int			get_open_server(int cs, char *name)
{
	struct stat	stat_record;
	int			fd;

	fd = 0;
	if ((fd = open(name, O_RDONLY, 0777)) == -1)
		write(cs, "ERR_DONT_EXIST", 14);
	else
	{
		fstat(fd, &stat_record);
		if (stat_record.st_size <= 1)
			write(cs, "ERR_EMPTY", 14);
		else
			write(cs, "SUCCESS", 14);
		return (fd);
	}
	return (0);
}

void		get_server(int cs, char **cmd)
{
	char	buf[1024];
	int		fd;
	int		r;

	if (command_validity(SRV, cmd))
	{
		if ((fd = get_open_server(cs, cmd[1])))
		{
			while ((r = read(fd, &buf, 1023)) > 0)
			{
				write(cs, buf, r);
				ft_bzero(&buf, 1024);
				if (r < 1023)
					break ;
			}
			close(fd);
		}
	}
	return ;
}
