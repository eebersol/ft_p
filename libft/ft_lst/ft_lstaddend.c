/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:14:23 by eebersol          #+#    #+#             */
/*   Updated: 2016/10/31 18:23:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*list;

	list = *alst;
	if ((*alst == NULL || (*alst)->content == NULL) && new)
		*alst = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}
