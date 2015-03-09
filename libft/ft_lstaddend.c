/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlelez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:29:37 by jlelez            #+#    #+#             */
/*   Updated: 2015/02/26 10:17:25 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (alst && new)
	{
		tmp = *alst;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new;
				new->next = NULL;
			}
			tmp = tmp->next;
		}
	}
}
