/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/19 16:18:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

void log_msg(char *str, int i)
{
	if (i == 0)
		printf("SUCCESS : %s\n", str);
	else if (i == 1)
		printf("ERROR : %s\n", str);
	else
	{
		printf("FATAL ERROR : %s\n", str);
		exit(0);
	}
}

void 	log_cd(int cs, int type, char *str, char *str2)
{
	char *ret;

	ret = NULL;
	if (type == SUCCESS)
	{
		ret = ft_strjoin("[server] SUCCESS : move  ", str);
		ret = ft_strjoin(ret , " -> ");
		ret = ft_strjoin(ret , str2);
		ret = ft_strjoin(ret, "\n");
		write(cs, ret, ft_strlen(ret));
	}
	if (type == ERROR)
	{
		if (str)
		{
			ret = ft_strjoin("[server] ERROR : Wrong path -> ", str);
			ret = ft_strjoin(ret, "\n");
			write(cs, ret, ft_strlen(ret));
		}
		else if (str2)
		{
			write(cs, str2, ft_strlen(str2));
		}
	}
}

void 	log_get(int cs, int type, char *str, char *file)
{
	char *ret;

	ret = NULL;
	if (type == ERROR)
	{
		if (str && file)
		{
			ret = ft_strjoin("[server] ERROR : ", str);
			ret = ft_strjoin(str, " ");
			ret = ft_strjoin(str, file);
		}
		else
			ret = ft_strjoin("[server] ERROR : open ", file);
		write(cs, ret, ft_strlen(ret));
	}
	if (type == SUCCESS)
	{
		ret = ft_strjoin("[server] SUCCESS : ", file);
		ret = ft_strjoin(file, "has been sent by server");
		write(cs, ret, ft_strlen(ret));
	}
}

void 	log_put(int cs, int type, char *str, char *file)
{
	char *ret;

	ret = NULL;
	if (type == ERROR)
	{
		if (str && file)
		{
			ret = ft_strjoin("[server] ERROR : ", str);
			ret = ft_strjoin(str, " ");
			ret = ft_strjoin(str, file);
		}
		else
			ret = ft_strjoin("[server] ERROR : open ", file);
		write(cs, ret, ft_strlen(ret));
	}
	if (type == SUCCESS)
	{
		ret = ft_strjoin("[server] SUCCESS : ", file);
		ret = ft_strjoin(file, "  has been received by server");
		write(cs, ret, ft_strlen(ret));
	}
}