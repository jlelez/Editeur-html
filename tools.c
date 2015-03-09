/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 20:37:50 by afouchar          #+#    #+#             */
/*   Updated: 2015/03/05 14:52:24 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

int		ft_mmtopx(int nb)
{
	return ((nb * 37.7953) / 10);
}

void		ft_swap(int *a, int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int		*ft_color_picker(t_env *e, int x, int y)
{
	int		*colors;

	colors = (int *)malloc(sizeof(int) * 4);
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
	if (e->data != NULL && x >= 0 && y >= 0 && x < e->width && y < e->height)
	{
		colors[0] = ((((unsigned int *)e->data)[y * e->width + x] >> 16) & 0xFF);
		colors[1] = ((((unsigned int *)e->data)[y * e->width + x] >> 8) & 0xFF);
		colors[2] = ((((unsigned int *)e->data)[y * e->width + x]) & 0xFF);
	}
	return (colors);
}

int	ft_rgbtohex(int r, int g, int b)
{
	ft_putnbr(((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
	return (1);
}

int		*ft_page_bounds(t_env *e, int x, int x1, int y, int y1)
{
	int		*values;
	int		dif_x;
	int		dif_y;

	values = (int *)malloc(sizeof(int) * 4);
	if (x > x1)
		ft_swap(&x, &x1);
	if (y > y1)
		ft_swap(&y, &y1);
	dif_x = x1 - x;
	dif_y = y1 - y;
	if (x < e->page.padding + e->box.margin)
	{
		x = e->page.padding + e->box.margin;
		if (e->drag == 1)
			dif_x = x1 - x;
		x1 = x + dif_x;
	}
	if (x1 > (e->page.width - e->page.padding - e->box.margin))
	{
		x1 = (e->page.width - e->page.padding - e->box.margin);
		if (e->drag == 1)
			dif_x = x1 - x;
		x = x1 - dif_x;
	}
	if (y < e->page.padding + e->box.margin)
	{
		y = e->page.padding + e->box.margin;
		if (e->drag == 1)
			dif_y = y1 - y;
		y1 = y + dif_y;
	}
	if (y1 > (e->page.height - e->page.padding - e->box.margin))
	{
		y1 = (e->page.height - e->page.padding - e->box.margin);
		if (e->drag == 1)
			dif_y = y1 - y;
		y = y1 - dif_y;
	}
	values[0] = x;
	values[1] = x1;
	values[2] = y;
	values[3] = y1;
	return (values);
}

void		ft_save_list(t_env *e)
{
	t_box	tmp;

	tmp.x = e->select.x;
	tmp.x1 = e->select.x1;
	tmp.y = e->select.y;
	tmp.y1 = e->select.y1;
	tmp.content = ft_strdup(e->box.content);
	tmp.font_size = e->box.font_size;
	tmp.margin = e->box.margin;
	tmp.align = 0;
	ft_putnbr(e->html.iweb);
	if (e->html.iweb == 0)
		e->coord = ft_lstnew(&tmp, sizeof(t_box));
	if (e->html.iweb > 0)
	{
		e->newlist = ft_lstnew(&tmp, sizeof(t_box));
		ft_lstaddend(&e->coord, e->newlist);
	}
	e->html.iweb++;
}

int		*ft_repulse_first(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (x >= set.x && x <= set.x1 && y >= set.x && y <= set.y1)
		{
			values[0] = set.x1 - x;
			values[1] = set.y1 - y;
			if (values[0] <= values[1])
			{
				values[0] = set.x1 + (e->box.margin * 2);
				values[1] = y;
			}
			else if (values[1] < values[0])
			{
				values[1] = set.y1 + (e->box.margin * 2);
				values[0] = x;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}

int		*ft_repulse_second(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (x >= set.x && x <= set.x1 && y >= set.x && y <= set.y1)
		{
			values[0] = x - set.x;
			values[1] = y - set.y;
			if (values[0] <= values[1])
			{
				values[0] = set.x - e->box.margin;
				values[1] = y;
			}
			else if (values[1] < values[0])
			{
				values[1] = set.y - e->box.margin;
				values[0] = x;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}

int		*ft_magnet_right(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (x > set.x1)
		{
			if (y > (set.y - 40) && y < (set.y + 40))
			{
				if (x < (set.x1 + 40))
					values[0] = set.x1 + e->box.margin;
				values[1] = set.y;
			}
			else if (y > (set.y1 - 40) && y < (set.y1 + 40))
			{
				if (x < (set.x1 + 40))
					values[0] = set.x1 + e->box.margin;
				values[1] = set.y1;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}

int		*ft_magnet_bottom(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (y > set.y1)
		{
			if (x > (set.x - 40) && x < (set.x + 40))
			{
				if (y < (set.y1 + 40))
					values[1] = set.y1 + e->box.margin;
				values[0] = set.x;
			}
			else if (x > (set.x1 - 40) && x < (set.x1 + 40))
			{
				if (y < (set.y1 + 40))
					values[1] = set.y1 + e->box.margin;
				values[0] = set.x1;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}

int		*ft_magnet_left(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (x < set.x)
		{
			if (y > (set.y - 40) && y < (set.y + 40))
			{
				if (x < (set.x + 40))
					values[0] = set.x - e->box.margin;
				values[1] = set.y;
			}
			else if (y > (set.y1 - 40) && y < (set.y1 + 40))
			{
				if (x < (set.x + 40))
					values[0] = set.x - e->box.margin;
				values[1] = set.y;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}

int		*ft_magnet_top(t_env *e, int x, int y)
{
	int		*values;
	t_box		set;
	t_list		*list;

	list = e->coord;
	values = (int *)malloc(sizeof(int) * 3);
	values[0] = x;
	values[1] = y;
	while (list)
	{
		set.x = ((t_box*)(list->content))->x;
		set.y = ((t_box*)(list->content))->y;
		set.x1 = ((t_box*)(list->content))->x1;
		set.y1 = ((t_box*)(list->content))->y1;
		if (x > set.x)
		{
			if (y > (set.y - 40) && y < (set.y + 40))
			{
				if (x > (set.x + 40))
					values[0] = set.x - e->box.margin;
				values[1] = set.y;
			}
			else if (y > (set.y1 - 40) && y < (set.y1 + 40))
			{
				if (x > (set.x + 40))
					values[0] = set.x - e->box.margin;
				values[1] = set.y;
			}
			return (values);
		}
		list = list->next;
	}
	return (values);
}
