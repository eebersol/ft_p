/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:03:06 by eebersol          #+#    #+#             */
/*   Updated: 2016/01/30 14:40:20 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** NAME : strclr (unofficial)
** DESCRIPTION : vider une chaine de caractere en la remplissant de \0
** PARAM : s -> la chaire qui doit etre vidée
*/

void	ft_strclr(char *s)
{
	if (s != NULL)
	{
		while (*s)
		{
			*s = '\0';
			s++;
		}
	}
}
