/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 16:21:40 by afouchar          #+#    #+#             */
/*   Updated: 2015/03/05 14:51:57 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

void	ft_display(t_env *e, t_color *c, int x, int y)
{
	if (e->data != NULL && x >= 0 && y >= 0 && x < e->width && y < e->height)
		((unsigned int *)e->data)[y * e->width + x] = RGB;
}

int		expose_hook(t_env *e)
{
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->sl), &(e->end));
	
	ft_display_layout(e);
	ft_display_sidebar(e);
	ft_ui(e);
	ft_display_save_button(e);
	ft_display_magnet(e);
	ft_display_button_font_family(e);

	if (e->select.x != 0 && e->select.x1 != 0
	&& e->select.y != 0 && e->select.y1 != 0)
		ft_display_boxes(e);

	if (e->coord)
		ft_display_all_boxes(e);

	if (e->drag_file == 1)
		ft_display_file_icon(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (e->coord)
		ft_display_dropped_name(e);
	if (e->file_saved == 1)
		ft_say_saved(e);
	if (e->coord)
		ft_display_font_size(e);
	ft_display_font_family(e);
	ft_display_files(e);
	ft_write_ui(e);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}

void	ft_display_button_font_family(t_env *e)
{	
	int x;
	int y;
	t_color c;
	
	x = e->button.x;
	y = 200;
	c.r = e->button.b_color.r + 30;
	c.g = e->button.b_color.g + 30;
	c.b = e->button.b_color.b + 30;
	while (y <= 220)
	{
		while (x <= e->button.x1)
		{
			ft_display(e, &e->button.b_color, x, y);
			x++;
		}
		x = e->button.x;
		y++;
	}
	x = e->button.x - 140;
	y = 200;
	while (y <= 220)
	{
		while (x <= e->button.x - 5)
		{
			ft_display(e, &c, x, y);
			x++;
		}
		c.r++;
		c.g++;
		c.b++;
		x = e->button.x - 140;
		y++;
	}
}

void	ft_display_font_family(t_env *e)
{
	mlx_string_put(e->mlx, e->win, e->button.x - 130, 215, e->sidebar.txt_color, e->tabfont_family[e->tabindex]);
	mlx_string_put(e->mlx, e->win, e->button.x + 8, 218, e->sidebar.txt_color, "^");
}

void	ft_display_button_align(t_env *e, int x, int y1, int align)
{
	int x1;
	int y;
	t_color c;

	c.r = 245;
	c.g = 245;
	c.b = 245;
	x1 = x + 15;
	y = y1 - 15;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if (x > x1 - 13 && x < x1 - 2 && y > y1 - 13 && y < y1 - 10)
				ft_display(e, &e->button.b_color, x, y);
			else if (x > x1 - 13 && x < x1 - 2 && y > y1 - 5 && y < y1 - 2)
				ft_display(e, &e->button.b_color, x, y);
			else if (x > x1 - 13 && x < x1 - 6 && y > y1 - 9 && y < y1 - 6 && align == 0)
				ft_display(e, &e->button.b_color, x, y);
			else if (x > x1 - 11 && x < x1 - 4 && y > y1 - 9 && y < y1 - 6 && align == 1)
				ft_display(e, &e->button.b_color, x, y);
			else if (x > x1 - 9 && x < x1 - 2 && y > y1 - 9 && y < y1 - 6 && align == 2)
				ft_display(e, &e->button.b_color, x, y);
			else	
				ft_display(e, &c, x, y);
			x++;
		}
		x = x1 - 15;
		y++;
	}
}

void	ft_display_magnet(t_env *e)
{
	int		x;
	int		y;
	int		ys;
	t_color		c;

	x = e->button.x - 180;
	y = e->button.y1 + 2;
	ys = e->button.y1 - e->button.y;
	ys = e->button.y1 + ys;
	c.r = 96;
	c.g = 96;
	c.b = 96;
	if (e->magnet == 1)
	{
		c.r = 255;
		c.g = 51;
		c.b = 51;
	}
	while (y <= ys)
	{
		while (x <= e->button.x1 - 140)
		{
			ft_display(e, &c, x, y);
			x++;
		}
		x = e->button.x - 180;
		y++;
	}
}

void	ft_display_dropped_name(t_env *e)
{
	int		x;
	int		y;
	t_box		write;
	t_list		*txt;

	txt = e->coord;
	while (txt)
	{
		write.x = ((t_box*)(txt->content))->x;
		write.y = ((t_box*)(txt->content))->y;
		write.x1 = ((t_box*)(txt->content))->x1;
		write.y1 = ((t_box*)(txt->content))->y1;
		write.content = ((t_box*)(txt->content))->content;
		x = write.x + (write.x1 - write.x) / 3;
		y = write.y + (write.y1 - write.y) / 2;
		if (write.content != NULL)
			mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, write.content);
		txt = txt->next;
	}
}

void	ft_display_font_size(t_env *e)
{
	int		x;
	int		y;
	t_box		write;
	t_list		*txt;

	txt = e->coord;
	while (txt)
	{
		write.x = ((t_box*)(txt->content))->x;
		write.y = ((t_box*)(txt->content))->y;
		write.x1 = ((t_box*)(txt->content))->x1;
		write.y1 = ((t_box*)(txt->content))->y1;
		write.font_size = ((t_box*)(txt->content))->font_size;
		x = write.x + 20;
		y = write.y + 13;
		if (write.font_size > 0)
		{
			mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(write.font_size));
			x += (ft_strlen(ft_itoa(write.font_size)) * 8);
			y = write.y + 13;
			mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "px");
		}
		txt = txt->next;
	}
}

void	ft_display_all_boxes(t_env *e)
{
	int		x;
	int		y;
	t_box		draw;
	t_list		*tmp;

	if (e->coord)
	{
		tmp = e->coord;
		while (tmp)
		{	
			draw.x = ((t_box*)(tmp->content))->x;
			draw.y = ((t_box*)(tmp->content))->y;
			draw.x1 = ((t_box*)(tmp->content))->x1;
			draw.y1 = ((t_box*)(tmp->content))->y1;
			draw.content = ((t_box*)(tmp->content))->content;
			draw.align = ((t_box*)(tmp->content))->align;
			x = draw.x;
			y = draw.y;
			while (y <= draw.y1)
			{
				while (x <= draw.x1)
				{
					ft_display(e, &e->box.elem_color, x, y);
					x++;
				}
				x = draw.x;
				y++;
			}
			ft_display_delete(e, draw.x1 - 1, draw.y + 1);
			ft_display_grab(e, draw.x1 - 1, draw.y + 1);
			ft_display_fontsize(e, draw.x + 1, draw.y + 1);
			ft_display_button_align(e, draw.x + 1, draw.y1 - 1, draw.align);
			tmp = tmp->next;
		}
	}

}

void	ft_display_save_button(t_env *e)
{
	int		x;
	int		y;
	t_color		c;

	x = e->button.x - 180;
	y = e->button.y;
	c.r = 96;
	c.g = 96;
	c.b = 96;
	while (y <= e->button.y1)
	{
		while (x <= e->button.x1 - 140)
		{
			ft_display(e, &c, x, y);
			x++;
		}
		x = e->button.x - 180;
		y++;
	}
}

void	ft_display_file_icon(t_env *e)
{
	int		x;
	int		x1;
	int		y;
	int		y1;
	t_color		c;

	x = e->drop_file.x1 - 5;
	x1 = x + 19;
	y = e->drop_file.y1 - 5;
	y1 = y + 25;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if (y == e->drop_file.y1 - 5 || y == y1
					|| x == e->drop_file.x1 - 5 || x == x1)
			{
				c.r = 32;
				c.g = 32;
				c.b = 32;
			}
			else
			{
				c.r = 245;
				c.g = 245;
				c.b = 245;
			}
			ft_display(e, &c, x, y);
			x++;
		}
		x = e->drop_file.x1 - 5;
		y++;
	}
}

void	ft_display_boxes(t_env *e)
{
	int		x;
	int		y;
	int		*values;

	values = ft_page_bounds(e, e->select.x, e->select.x1, e->select.y, e->select.y1);
	e->box.x = values[0];
	e->box.x1 = values[1];
	e->box.y = values[2];
	e->box.y1 = values[3];
	x = e->box.x;
	y = e->box.y;
	ft_boxes_margin(e);
	while (y <= e->box.y1)
	{
		while (x <= e->box.x1)
		{
			ft_boxes_padding(e, x, y);
			ft_display(e, &e->box.elem_color, x, y);
			x++;
		}
		x = e->box.x;
		y++;
	}
	x = e->box.x + (e->box.x1 - e->box.x) / 3;
	y = e->box.y + (e->box.y1 - e->box.y) / 2;
	ft_display_delete(e, e->box.x1 - 1, e->box.y + 1);
	ft_display_grab(e, e->box.x1 - 1, e->box.y + 1);
	ft_display_fontsize(e, e->box.x + 1, e->box.y + 1);
	ft_display_button_align(e, e->box.x + 1, e->box.y1 - 1, e->box.align);
}

void	ft_display_fontsize(t_env *e, int x, int y)
{
	int		x1;
	int		y1;
	int		bx;
	int		by;
	t_color		c;

	x1 = x + 12;
	y1 = y + 12;
	bx = x + 3;
	by = y + 2;
	c.r = 245;
	c.g = 245;
	c.b = 245;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if (((x > bx && x < bx + 5) && (y == by || y == by + 1))
					|| ((x > bx && x < bx + 4) && (y == by + 3 || y == by + 4)))
				ft_display(e, &e->button.b_color, x, y);
			else if ((y > by && y < by + 8) && (x == bx || x == bx + 1))
				ft_display(e, &e->button.b_color, x, y);
			else
				ft_display(e, &c, x, y);
			x++;
		}
		x = x1 - 12;
		y++;
	}
	y++;
	y1 = y + 12;
	bx = x + 5;
	by = y + 4;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if (((x > bx && x < bx + 3) && y == by)
					|| ((x > bx && x < bx + 2) && y == by + 2))
				ft_display(e, &e->button.b_color, x, y);
			else if ((y > by && y < by + 6) && x == bx)
				ft_display(e, &e->button.b_color, x, y);
			else
				ft_display(e, &c, x, y);
			x++;
		}
		x = x1 - 12;
		y++;
	}
}

void	ft_display_delete(t_env *e, int x1, int y)
{
	int		x;
	int		y1;
	int		bx;
	int		by;
	t_color		c;

	x = x1 - 12;
	y1 = y + 12;
	bx = x + 2;
	by = y + 5;
	c.r = 245;
	c.g = 245;
	c.b = 245;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if ((x > bx && x < bx + 8) && (y == by || y == by + 1))
				ft_display(e, &e->button.b_color, x, y);
			else
				ft_display(e, &c, x, y);
			x++;
		}
		x = x1 - 12;
		y++;
	}
}

void	ft_display_grab(t_env *e, int x1, int y)
{
	int		x;
	int		y1;
	int		bx;
	int		by;
	t_color		c;

	x = x1 - 12;
	y += 14;
	y1 = y + 12;
	bx = x + 3;
	by = y + 3;
	c.r = 245;
	c.g = 245;
	c.b = 245;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if ((x >= bx && x <= bx + 6)
					&& (y == by || y == by - 1 || y == by + 6 || y == by + 7))
				ft_display(e, &e->button.b_color, x, y);
			else if ((y >= by && y <= by + 6)
					&& (x == bx || x == bx - 1 || x == bx + 6 || x == bx + 7))
				ft_display(e, &e->button.b_color, x, y);
			else
				ft_display(e, &c, x, y);
			x++;
		}
		x = x1 - 12;
		y++;
	}
}

void	ft_display_layout(t_env *e)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < e->page.height)
	{
		while (x < e->page.width)
		{
			ft_page_margin(e, x, y);
			ft_display(e, &e->page.bg_color, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_display_sidebar(t_env *e)
{
	int		x;
	int		y;

	x = e->sidebar.x;
	y = 0;

	while (y < e->sidebar.y1)
	{
		while (x < e->sidebar.x1)
		{
			ft_sidebar_gradient(e, x);
			ft_display(e, &e->sidebar.sb_color, x, y);
			x++;
		}
		x = e->sidebar.x;
		y++;
	}
	ft_display_palette(e);
	ft_display_separator(e);
}

void	ft_display_palette(t_env *e)
{
	int		x;
	int		xs;
	int		y;
	int		ys;
	int		i;

	x = e->sidebar.x + 54;
	xs = x + 13;
	y = 298 - 38;
	ys = y + 13;
	i = 0;
	while (i < 117)
	{
		while (y < ys)
		{
			while (x < xs)
			{
				ft_color_palette(e, i);
				ft_display(e, &e->palette, x, y);
				x++;
			}
			x = xs - 13;
			y++;
		}
		y = ys - 13;
		x = xs + 1;
		xs = x + 13;
		if ((i + 1) % 13 == 0)
		{
			y = ys + 1;
			ys = y + 13;
			x = e->sidebar.x + 54;
			xs = x + 13;
		}
		i++;
	}
}

void	ft_display_separator(t_env *e)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = (e->sidebar.x);
	y = ((e->height / 2) - 13);
	while (i <= (e->nb_files + 1))
	{
		while (x < e->sidebar.x1)
		{
			ft_display(e, &e->sidebar.lines, x, y);
			x++;
		}
		x = e->sidebar.x;
		y += 18;
		i++;
	}
}

void		ft_display_files(t_env *e)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = (e->sidebar.x + 28);
	y = (e->height / 2);
	while (e->file_list[i] != NULL)
	{
		mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, e->file_list[i]);
		y += 18;
		i++;
	}
}

void	ft_display_selection(t_env *e)
{
	int		x;
	int		y;
	int		*values;

	values = ft_page_bounds(e, e->select.x, e->select.x1, e->select.y, e->select.y1);
	x = values[0];
	y = values[2];
	while (y <= values[3])
	{
		while(x <= values[1])
		{
			if (x == values[0] || x == values[1])
				ft_display(e, &e->select.select_color, x, y);
			else if (y == values[2] || y == values[3])
				ft_display(e, &e->select.select_color, x, y);
			x++;
		}
		x = values[0];
		y++;
	}
}
