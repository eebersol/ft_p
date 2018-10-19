/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:28:55 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int		put_open_client(char *name)
{
	struct stat		stat_record;
	int				ret;
	int				fd;

	fd = 0;
	ret = fstat(fd, &stat_record);
	if ((fd = open(name, O_RDONLY, 0777)) == -1)
		printf(RED "client - error : file %s don't exist." RESET "\n", name);
	else
	{
		fstat(fd, &stat_record);
		if (stat_record.st_size <= 1)
			printf(RED "client - error : file %s empty" RESET "\n", name);
		else
			return (fd);
	}
	return (0);
}

int		put_server_response(int cs, char *name)
{
	char	buf[1024];
	int		r;

	r = read(cs, buf, 1023);
	buf[r] = '\0';
	if (ft_strcmp(buf, "SUCCESS") == 0)
	{
		printf(GRN "client - success : %s has been send" RESET"\n", name);
		return (1);
	}
	else if (ft_strcmp(buf, "ERR_EXIST") == 0)
	{
		printf(RED "client - error : file %s exist." RESET "\n", name);
		return (0);
	}
	return (1);
}

int		put_client(char **cmd, int cs)
{
	char	buf[1024];
	char	*message;
	int		r;
	int		fd;

	message = NULL;
	if (command_validity(CLT, cmd) && (fd = put_open_client(cmd[1])))
	{
		message = ft_strjoin(ft_strjoin(cmd[0], " "), cmd[1]);
		message = ft_strjoin(message, "\n");
		send(cs, message, ft_strlen(message), 0);
		if (put_server_response(cs, cmd[1]))
		{
			while ((r = read(fd, &buf, 1023)) > 0)
			{
				write(cs, buf, r);
				ft_bzero(&buf, 1024);
				if (r < 1023)
					break ;
			}
		}
		close(fd);
	}
	return (0);
}
