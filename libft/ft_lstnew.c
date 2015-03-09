/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlelez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:03:40 by jlelez            #+#    #+#             */
/*   Updated: 2015/01/19 20:45:55 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlist;

	newlist = malloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	if ((content == NULL) || (content_size == 0))
	{
		newlist->content = NULL;
		newlist->content_size = 0;
		return (newlist);
	}
	newlist->content = malloc(content_size);
	if (newlist->content == NULL)
		return (NULL);
	newlist->content_size = content_size;
	newlist->next = NULL;
	ft_memcpy(newlist->content, content, content_size);
	return (newlist);
}
