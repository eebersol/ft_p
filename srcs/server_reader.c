/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 18:05:46 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_p.h>



void	 get_file_server(int cs, char **cmd)
{
	char 	bufer[1024];
	int 	fd;
	int 	r;

	if (!cmd[1])
		return (log_get(cs, ERROR, "get need one argument", cmd[1]));
	if (cmd[2])
		return (log_get(cs, ERROR, "get to many argument", cmd[1]));
	if ((fd = open(cmd[1], O_APPEND, 0777)) == -1)
		return (log_get(cs, ERROR, NULL, cmd[1]));
	while((r = read(fd, &bufer, 1023)) > 0)
	{
		bufer[r] = '\0';
		write(cs, bufer, r);
		ft_bzero(&bufer, 1024);
		if (r != 1023)
			break;
	}
	return (log_get(cs, SUCCESS, NULL, cmd[1]));
	close (fd);

}

void	put_file_server(int cs, char **cmd)
{
	int 	fd;
	char 	buf[1024];
	int 	r;

	if (!cmd[1])
		return (log_put(cs, ERROR, "put need one argument", cmd[1]));
	if (cmd[2])
		return (log_put(cs, ERROR, "put to many argument", cmd[1]));
	if ((fd = open(cmd[1], O_APPEND, 0777)) == -1)
		log_put(cs, ERROR, NULL, cmd[1]);
	while((r = read(cs, &buf, 1023)) > 0)
	{
		write(fd, buf, r);
		ft_bzero(&buf, 1024);
		if (r < 1023)
		{
			write(cs, "\n", 1);
			break;
		}
	}
	close(fd);
	return (log_put(cs, SUCCESS, NULL, cmd[1]));
}

int	find_cmd_server(char **cmd, int cs, char *path)
{	
	if (ft_strcmp(cmd[0], "ls") == 0)
		ls_server(cs);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_server(cmd, cs, path);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd_server(cs, cmd);
	else if (ft_strcmp(cmd[0], "put") == 0 || ft_strcmp(cmd[0], "get") == 0)
		return (1);
	else
		write(cs, "[server] ERROR : Command not found.\n", 36); 
	return (0);
}

int 	reader(int cs, char *path)
{
	char 	buf[1024];
	char 	**cmd;
	int 	r;

	cmd = NULL;
	while((r = read(cs, &buf, 1023)) > 0)
	{
		buf[r] = '\0';
		cmd = ft_strsplit(buf, ' ');
		if (find_cmd_server(cmd, cs, path) == 1)
			break ;
		ft_bzero(&buf, 1024);
	}
	if (ft_strcmp(cmd[0], "put") == 0)
	{
		put_file_server(cs, cmd);
		reader(cs, path);
	}
	else if (ft_strcmp(cmd[0], "get") == 0)
	{
		get_file_server(cs, cmd);
		reader(cs, path);
	}
	return (r);
}