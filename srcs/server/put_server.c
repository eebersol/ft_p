/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:31:52 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int			put_open_server(char *name, int cs)
{
	int		fd;

	fd = 0;
	if ((fd = open(name, O_RDONLY, 0777)) != -1)
		write(cs, "ERR_EXIST", 9);
	else if ((fd = open(name, O_CREAT | O_WRONLY, 0777)) == -1)
		write(cs, "ERR_OPEN", 8);
	else
	{
		write(cs, "SUCCESS", 7);
		return (fd);
	}
	close(fd);
	return (0);
}

void		put_server(int cs, char **cmd)
{
	char	buf[1024];
	int		fd;
	int		r;

	if (command_validity(SRV, cmd))
	{
		if ((fd = put_open_server(cmd[1], cs)))
		{
			while ((r = read(cs, &buf, 1023)) > 0)
			{
				write(fd, buf, r);
				ft_bzero(&buf, 1024);
				if (r < 1023)
					break ;
			}
		}
		close(fd);
	}
	return ;
}
