/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:26:15 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int		get_server_response(int cs, char **cmd)
{
	char	buf[1024];
	int		r;

	r = read(cs, buf, 1023);
	buf[r] = '\0';
	if (ft_strcmp(buf, "SUCCESS") == 0)
	{
		printf(GRN"server - success : %s has been send " RESET "\n", cmd[1]);
		return (1);
	}
	else if (ft_strcmp(buf, "ERR_DONT_EXIST") == 0)
	{
		unlink(cmd[1]);
		printf(RED "server - error : file %s don't exist." RESET "\n", cmd[1]);
		return (0);
	}
	else if (ft_strcmp(buf, "ERR_EMPTY") == 0)
	{
		unlink(cmd[1]);
		printf(RED "server - error : empty file." RESET "\n");
		return (0);
	}
	return (0);
}

int		get_open_client(char *name)
{
	int		fd;

	fd = 0;
	if ((fd = open(name, O_RDONLY, 0777)) != -1)
		printf(RED "client - error: file %s, exist." RESET "\n", name);
	else if ((fd = open(name, O_CREAT | O_WRONLY, 0777)) == -1)
		printf(RED "client - error : open %s fail." RESET "\n", name);
	else
		return (fd);
	return (0);
}

int		get_client(char **cmd, int cs)
{
	char	buf[1024];
	char	*message;
	int		fd;
	int		r;

	if (command_validity(CLT, cmd) && (fd = get_open_client(cmd[1])))
	{
		message = ft_strjoin(ft_strjoin(cmd[0], " "), cmd[1]);
		message = ft_strjoin(message, "\n");
		send(cs, message, ft_strlen(message), 0);
		if (get_server_response(cs, cmd))
		{
			while ((r = read(cs, buf, 1023)) > 0)
			{
				write(fd, buf, r);
				if (r < 1023)
					break ;
				ft_bzero(&buf, 1024);
			}
		}
		close(fd);
	}
	return (0);
}
