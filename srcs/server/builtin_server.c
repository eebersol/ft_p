/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/27 13:48:17 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void	cd_server_response(int cs, int flag)
{
	if (flag == -1)
		write(cs, "server - error : wrong path.\n", 29);
	else if (flag == 0)
		write(cs, "server - success.\n", 18);
	else
		write(cs, "server - ERROR : Hors zone.\n", 28);
}

void	cd_server(char **cmd, int cs, char *path)
{
	char	old_pwd[2048];
	char	new_pwd[2048];
	int		flag;

	getcwd(old_pwd, 2048);
	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
		flag = chdir(path);
	else if (ft_strcmp(cmd[1], "..") == 0)
		flag = cd_move_back(old_pwd, path);
	else
		flag = chdir(ft_strjoin(ft_strjoin(old_pwd, "/"), cmd[1]));
	getcwd(new_pwd, 2048);
	return (cd_server_response(cs, flag));
}

void	pwd_server(int cs, char **cmd)
{
	char	pwd[2048];
	char	*res;

	res = NULL;
	if (cmd[1])
		write(cs, "server - error : to many argument\n", 34);
	else
	{
		getcwd(pwd, 2048);
		res = ft_strjoin("server - success : ", pwd);
		res = ft_strjoin(res, "\n");
		write(cs, res, ft_strlen(res));
	}
	return ;
}

void	ls_server(int socket)
{
	pid_t	pid;
	char	*cmd[2];
	int		flag;
	int		status;

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
