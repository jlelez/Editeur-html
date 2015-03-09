/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 17:02:59 by afouchar          #+#    #+#             */
/*   Updated: 2015/03/05 14:51:41 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

int		key_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == 115)
	{
		ft_save(e);
		e->file_saved = 1;
	}
	expose_hook(e);
	return (0);
}

int		mouse_hook(int x, int y, t_env *e)
{
	int		dif_move_x;
	int		dif_move_y;
	int 	*xy;

	/*MOVE BOX*/
	if (e->move == 0 && e->drag_file == 0 && e->drag == 0 && x >= e->box.x1 - 13 && x <= e->box.x1 - 1
			&& y >= e->box.y + 13 && y <= e->box.y + 25)
	{
		e->move_box.x = x;
		e->move_box.y = y;
		e->move = 1;
	}
	else if (e->move == 1 && e->drag_file == 0 && e->drag == 0)
	{
		dif_move_x = e->move_box.x - x;
		dif_move_y = e->move_box.y - y;
		if (x != e->move_box.x)
		{
			e->select.x -= dif_move_x;
			e->select.x1 -= dif_move_x;
		}
		if (y != e->move_box.y)
		{
			e->select.y -= dif_move_y;
			e->select.y1 -= dif_move_y;
		}
		e->move_box.x = x;
		e->move_box.y = y;
	}
	/*DRAG & DROP FILE*/
	else if (e->move == 0 && e->drag_file == 0 && e->drag == 0 && x > e->sidebar.x
			&& x < e->sidebar.x1 && y > ((e->height / 2) - 13)
			&& y < ((e->height / 2) + (18 * e->nb_files)))
	{
		e->drop_file.x = x;
		e->drop_file.y = y;
		e->drag_file = 1;
		e->select.content = ft_drag_file(e, e->drop_file.y);
	}
	else if (e->move == 0 && e->drag_file == 1 && e->drag == 0)
	{
		e->drop_file.x1 = x;
		e->drop_file.y1 = y;
	}
	/*DRAW BOX*/
	else if (e->drag_file == 0 && e->move == 0)
	{
		if (e->drag == 0 && x < e->sidebar.x)
		{
			e->select.x = x;
			e->select.y = y;
			if (e->coord)
			{
				xy = ft_repulse_first(e, e->select.x, e->select.y);
				if (e->magnet == 1)
				{
					xy = ft_magnet_right(e, xy[0], xy[1]);
					xy = ft_magnet_bottom(e, xy[0], xy[1]);
					if (xy[0] == e->select.x && xy[1] == e->select.y)
					{
						xy = ft_magnet_left(e, xy[0], xy[1]);
						xy = ft_magnet_top(e, xy[0], xy[1]);
					}
				}
				e->select.x = xy[0];
				e->select.y = xy[1];
			}
			e->drag = 1;
		}
		else if (e->drag == 1 && x < e->sidebar.x)
		{
			e->select.x1 = x;
			e->select.y1 = y;
			if (e->coord)
			{
				xy = ft_repulse_second(e, e->select.x1, e->select.y1);
				if (e->magnet == 1)
				{
					xy = ft_magnet_right(e, xy[0], xy[1]);
					xy = ft_magnet_bottom(e, xy[0], xy[1]);
					if (xy[0] == e->select.x && xy[1] == e->select.y)
					{
						xy = ft_magnet_left(e, xy[0], xy[1]);
						xy = ft_magnet_top(e, xy[0], xy[1]);
					}
				}
				e->select.x1 = xy[0];
				e->select.y1 = xy[1];
			}
		}
		e->box.content = NULL;
	}
	expose_hook(e);
	return (0);
}

int		mouse_release(int button, int x, int y, t_env *e)
{
	int		*values;
	int		*xy;

	if (e->move == 1)
		e->move = 0;
	else if (button == 1 && e->drag == 1 && e->drag_file == 0 && e->select.x < e->sidebar.x)
	{
		values = ft_page_bounds(e, e->select.x, x, e->select.y, y);
		e->select.x = values[0];
		e->select.x1 = values[1];
		e->select.y = values[2];
		e->select.y1 = values[3];
		if (e->coord)
		{
			xy = ft_repulse_second(e, e->select.x1, e->select.y1);
			if (e->magnet == 1)
			{
				xy = ft_magnet_right(e, xy[0], xy[1]);
				xy = ft_magnet_bottom(e, xy[0], xy[1]);
				if (xy[0] == e->select.x && xy[1] == e->select.y)
				{
					xy = ft_magnet_left(e, xy[0], xy[1]);
					xy = ft_magnet_top(e, xy[0], xy[1]);
				}
			}
			e->select.x1 = xy[0];
			e->select.y1 = xy[1];
		}
		e->drag = 0;
		e->new_list = 1;
	}
	else if (button == 1 && e->drag == 0 && e->drag_file == 1 && e->drop_file.x > e->sidebar.x)
	{
		/*DROP FILE TO BOX*/
		e->box.content = ft_strdup(e->select.content);
		ft_putstr("file: ");
		ft_putstr(e->box.content);
		ft_putstr(" dropped to box\n");
		ft_save_list(e);
		e->drag_file = 0;
	}
	expose_hook(e);
	return (0);
}

int		mouse_press(int button, int x, int y, t_env *e)
{
	int		button_height;
	int		*colors;
	t_box	tmp;
	t_list	*tmpcoord;
	t_list	*tmpbefore;
	t_list	*tmpafter;

	colors = (int *)malloc(sizeof(int) * 4);
	button_height = e->button.y1 - e->button.y;
	if(button == 1)
	{
		/* page.padding + */
		if(x > e->button.x && x < e->button.x1
				&& y > e->button.y && y < e->button.y1)
		{
			e->page.padding_mm++;
			e->page.padding = ft_mmtopx(e->page.padding_mm);
			if (e->page.padding > ((e->page.width / 2) - 12))
			{
				e->page.padding_mm--;
				e->page.padding = ft_mmtopx(e->page.padding_mm);
			}
		}
		/* page.padding - */
		if(x > e->button.x && x < e->button.x1
				&& y > (e->button.y1 + 2) && y < (e->button.y1 + button_height + 2))
		{
			e->page.padding_mm--;
			e->page.padding = ft_mmtopx(e->page.padding_mm);
			if (e->page.padding_mm < 0 || e->page.padding < 0)
			{
				e->page.padding_mm = 0;
				e->page.padding = 0;
			}
		}
		/* box.margin + */
		if(x > e->button.x && x < e->button.x1
				&& y > (e->button.y1 + button_height + 7)
				&& y < (e->button.y1 + (button_height * 2) + 9))
		{
			e->box.margin_mm++;
			e->box.margin = ft_mmtopx(e->box.margin_mm);
			if (e->box.margin > (e->box.x1 - e->box.x))
			{
				e->box.margin_mm--;
				e->box.margin = ft_mmtopx(e->box.margin_mm);
			}
		}
		/* box.margin - */
		if(x > e->button.x && x < e->button.x1
				&& y > (e->button.y1 + (button_height * 2) + 11)
				&& y < (e->button.y1 + (button_height * 3) + 13))
		{
			e->box.margin_mm--;
			e->box.margin = ft_mmtopx(e->box.margin_mm);
			if (e->box.margin_mm < 0 || e->box.margin < 0)
			{
				e->box.margin_mm = 0;
				e->box.margin = 0;
			}
		}
		/* box.padding + */
		if(x > e->button.x && x < e->button.x1
				&& y > (e->button.y1 + (button_height * 3) + 18)
				&& y < (e->button.y1 + (button_height * 4) + 20))
		{
			e->box.padding_mm++;
			e->box.padding = ft_mmtopx(e->box.padding_mm);
			if (e->box.padding > (((e->box.x1 - e->box.x) / 2) - 12))
			{
				e->box.padding_mm--;
				e->box.padding = ft_mmtopx(e->box.padding_mm);
			}
		}
		/* box.padding - */
		if(x > e->button.x && x < e->button.x1
				&& y > (e->button.y1 + (button_height * 4) + 22)
				&& y < (e->button.y1 + (button_height * 5) + 24))
		{
			e->box.padding_mm--;
			e->box.padding = ft_mmtopx(e->box.padding_mm);
			if (e->box.padding_mm < 0 || e->box.padding < 0)
			{
				e->box.padding_mm = 0;
				e->box.padding= 0;
			}
		}
		/*save*/
		if (x > e->button.x - 180 && x < e->button.x1 - 140
				&& y > e->button.y && y < e->button.y1)
		{
			ft_save(e);
			e->file_saved = 1;
		}
		if (x > e->button.x - 180 && x < e->button.x1 - 140
				&& y > e->button.y1 && y < e->button.y1 + 22)
		{
			if (e->magnet == 1)
				e->magnet = 0;
			else if (e->magnet == 0)
				e->magnet = 1;
		}
		if (x > e->sidebar.x + 54 && x < e->button.x1
				&& y > 298 - 38 && y < 298 - 38 + (10 * 13))
		{
			colors = (ft_color_picker(e, x, y));
			e->page.new_color.r = colors[0];
			e->page.new_color.g = colors[1];
			e->page.new_color.b = colors[2];
		}
		/*Font family*/
		if (e->drag_file == 0 && e->drag == 0 && x <= e->button.x1 && x >= e->button.x && y <= 220 && y >= 200)
		{
			e->tabindex++;
			if (e->tabindex > 13)
				e->tabindex = 0;
		}
		/*Caracteristiques de chaque box*/
		if (e->coord)
		{
			tmpcoord = e->coord;
			tmpbefore = tmpcoord;
			while (tmpcoord)
			{
				tmp.x = ((t_box*)(tmpcoord->content))->x;	
				tmp.y = ((t_box*)(tmpcoord->content))->y;	
				tmp.x1 = ((t_box*)(tmpcoord->content))->x1;	
				tmp.y1 = ((t_box*)(tmpcoord->content))->y1;
				tmp.font_size = ((t_box*)(tmpcoord->content))->font_size;
				tmp.align = ((t_box*)(tmpcoord->content))->align;
				if (e->drag_file == 0 && e->drag == 0 && x >= tmp.x1 - 13 && x <= tmp.x1 - 1 && y >= tmp.y + 1 && y <= tmp.y + 13)
				{
					if (tmpcoord->next == NULL && e->coord != tmpcoord)
					{	
						free(tmpcoord);
						tmpcoord = NULL;
						tmpbefore->next = NULL;
					}
					else if (tmpcoord == e->coord)
					{
						if (e->coord->next == NULL)
						{
							free(tmpcoord);
							e->coord = NULL;
						}
						else
							e->coord = e->coord->next;
					}
					else
					{
						tmpafter = tmpcoord->next;
						tmpbefore->next = tmpafter;
						tmpcoord = tmpbefore;
					}
					e->html.iweb--;
				}
				if (e->drag_file == 0 && e->drag == 0 && x <= tmp.x + 15 && x >= tmp.x + 1 && y >= tmp.y1 - 15 && y <= tmp.y1 - 1)
				{
					tmp.align++;
					if (tmp.align > 2)
						tmp.align = 0;
					((t_box*)(tmpcoord->content))->align = tmp.align;
				}
				if (e->drag_file == 0 && e->drag == 0 && x <= tmp.x + 13 && x >= tmp.x + 1 && y >= tmp.y + 1 && y <= tmp.y + 13)
				{
					tmp.font_size++;
					((t_box*)(tmpcoord->content))->font_size = tmp.font_size;
				}
				if (e->drag_file == 0 && e->drag == 0 && x <= tmp.x + 13 && x >= tmp.x + 1 && y >= tmp.y + 13 && y <= tmp.y + 25)
				{
					if (tmp.font_size > 1)
						tmp.font_size--;
					((t_box*)(tmpcoord->content))->font_size = tmp.font_size;
				}
				if (tmpcoord)
				{
					tmpbefore = tmpcoord;
					tmpcoord = tmpcoord->next;
				}
				if (e->coord == NULL)
				{
					e->html.iweb = 0;
					e->select.x = 0;
					e->select.y = 0;
					e->select.x1 = 0;
					e->select.y1 = 0;
				}
			}
		}
	}
	expose_hook(e);
	return (0);
}
