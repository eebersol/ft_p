/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:25:18 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

int			cd_client_response(int flag)
{
	if (flag == -1)
		printf(RED"client - error : wrong path"RESET"\n");
	else if (flag == 0)
		printf(GRN"client - success."RESET"\n");
	else
		printf(RED"client - ERROR : Hors zone."RESET"\n");
	return (0);
}

int			cd_client(char **cmd, char *path)
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
	return (cd_client_response(flag));
}

int			pwd_client(char **cmd)
{
	char	pwd[2048];

	if (cmd[1])
		printf(RED"client - error : too many argument."RESET"\n");
	else
	{
		getcwd(pwd, 2048);
		printf(GRN"client - success : %s"RESET"\n", pwd);
	}
	return (0);
}

int			ls_client(char **cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		flag;
	int		status;

	flag = 0;
	if ((pid = fork()) == 0)
	{
		execve("/bin/ls", cmd, NULL);
		exit(0);
	}
	while ((wpid = wait(&status)) > 0)
		flag++;
	return (0);
}

void		client_quit(int socket)
{
	close(socket);
	exit(0);
}
