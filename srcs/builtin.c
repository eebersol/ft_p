/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 15:31:46 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void 	cd(char **cmd)
{
	char	old_pwd[2048];
	char	new_pwd[2048];
	char 	*str;

	getcwd(old_pwd, 2048);
	str = NULL;
	if (ft_strcmp(cmd[1], "..") == 0)
	{
		str = ft_strrchr(old_pwd, '/');
		str = ft_strsub(old_pwd, 0, ft_strlen(old_pwd)- ft_strlen(str));
		if (ft_strstr(str, recover_env()->racine) == NULL)
			write(recover_env()->socket, "Hors zone.\n", 11);
		else 
		{
			chdir(str);
			write(recover_env()->socket, "\n", 1);
		}
	}
	else
	{
		chdir(ft_strjoin(ft_strjoin(old_pwd, "/"), cmd[1]));
		write(recover_env()->socket, "\n", 1); 
	}
	getcwd(new_pwd, 2048);
	return ;
}

void 	pwd(void)
{
	char	pwd[2048];

	getcwd(pwd, 2048);
	write(recover_env()->socket, ft_strjoin(pwd, "\n"), ft_strlen(pwd) + 1);
	return ;
}
