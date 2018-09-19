/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 17:52:15 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void 	cd_client(char **cmd, char *path)
{
	char	old_pwd[2048];
	char	new_pwd[2048];
	char 	*str;
	int 	flag;

	getcwd(old_pwd, 2048);
	str = NULL;
	if (!cmd[1])
		flag = chdir(path);
	else if (ft_strcmp(cmd[1], "..") == 0)
	{
		str = ft_strrchr(old_pwd, '/');
		str = ft_strsub(old_pwd, 0, ft_strlen(old_pwd) - ft_strlen(str));
		if (ft_strstr(str, path) == NULL)
		{
			printf("[client] ERROR : Hors Zone\n");
			return ;
		}
		else 
			flag = chdir(str);
	}
	else
		flag = chdir(ft_strjoin(ft_strjoin(old_pwd, "/"), cmd[1]));
	getcwd(new_pwd, 2048);
	if (flag == -1)
		printf("[client] ERROR : Wrong path [%s]\n", cmd[1]);
	else
		printf("[client] SUCCESS : move  %s -> %s\n", old_pwd, new_pwd);
	return ;
}

void 	pwd_client(char **cmd)
{
	char	pwd[2048];

	if (cmd[1])
		printf("[client] ERROR : too many argument\n");
	else
	{
		getcwd(pwd, 2048);
		printf("[client] SUCCESS : %s\n", pwd);
	}
	return ;
}

void		ls_client(char **cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		flag;
	int 	status;

	flag = 0;
	if ((pid = fork()) == 0) 
	{
		execve("/bin/ls", cmd, NULL);
		exit(0);
	}
	while ((wpid = wait(&status)) > 0);
	return ;
}

void 	client_quit(int socket)
{
	close(socket);
	exit(0);
}