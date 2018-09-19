/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 17:53:21 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void 	cd_server(char **cmd, int cs, char *path)
{
	char	old_pwd[2048];
	char	new_pwd[2048];
	char 	*str;
	int 	flag;

	getcwd(old_pwd, 2048);
	str = NULL;
	if (!cmd[1])
		flag = chdir(path);
	if (ft_strcmp(cmd[1], "..") == 0)
	{
		str = ft_strrchr(old_pwd, '/');
		str = ft_strsub(old_pwd, 0, ft_strlen(old_pwd)- ft_strlen(str));
		if (ft_strstr(str, path) == NULL)
			return (log_cd(cs, ERROR, NULL, "[server] ERROR : Hors zone\n"));
		else 
			flag = chdir(str);
	}
	else
		flag = chdir(ft_strjoin(ft_strjoin(old_pwd, "/"), cmd[1]));
	getcwd(new_pwd, 2048);
	if (flag == -1)
		return (log_cd(cs, ERROR,cmd[1], NULL));
	else
		return (log_cd(cs, SUCCESS, old_pwd, new_pwd));
	return ;
}

void 	pwd_server(int cs, char **cmd)
{
	char	pwd[2048];
	char 	*res;

	res = NULL;
	if (cmd[1])
		write(cs, "[server] ERROR : to many argument", 24);
	else
	{
		getcwd(pwd, 2048);
		res = ft_strjoin("[server] SUCCESS : ", pwd);
		res = ft_strjoin(res, "\n");
		write(cs, res, ft_strlen(res));
	}
	return ;
}

void		ls_server(int socket)
{
	pid_t	pid;
	int		flag;
	char 	*cmd[2];
	int 	status;

	flag = 0;
	cmd[0] = "/bin/ls";
	cmd[1] = NULL;
	dup2(socket, 1);
	dup2(socket, 2);
	if ((pid = fork()) == 0)
		execve(cmd[0], cmd, NULL);
	wait4(pid, &status, -1, NULL);
	close(1);
	close(2);
	return ;
}