/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/29 15:32:47 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_p.h"

int		cd_move_back(char *old_pwd, char *path)
{
	char *str;

	str = ft_strrchr(old_pwd, '/');
	str = ft_strsub(old_pwd, 0, ft_strlen(old_pwd) - ft_strlen(str));
	if (ft_strstr(str, path) == NULL)
		return (1);
	else
		return (chdir(str));
}

int		command_validity(char *type, char **cmd)
{
	if (!cmd[1])
		printf(RED "%s - ERROR : %s need argument. " RESET "\n", type,
															cmd[0]);
	else if (cmd[2])
		printf(RED"%s - ERROR : %st to many argument. " RESET "\n",
															type, cmd[0]);
	else
		return (1);
	return (0);
}
