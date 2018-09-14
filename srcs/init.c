/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 15:00:21 by eebersol          #+#    #+#             */
/*   Updated: 2018/09/14 15:12:25 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_p.h"

t_env	*recover_env(void)
{
	static t_env	env;

	return (&env);
}

t_env	*init_env(void)
{
	t_env 	*env;

	env = recover_env();
	env->socket = 0;
	env->racine = (char*)malloc(sizeof(char) * 2048);
	getcwd(env->racine, 2048);
	return (env);
}
