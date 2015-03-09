/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 18:51:09 by afouchar          #+#    #+#             */
/*   Updated: 2015/02/26 17:28:41 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

void	ft_page_margin(t_env *e, int x, int y)
{
	int		pad;

	pad = e->page.padding;
	if ((x >= pad && x <= (e->page.width - pad))
	&& (y == pad || y == (e->page.height - pad)))
	{
		e->page.bg_color.r = 215;
		e->page.bg_color.g = 215;
		e->page.bg_color.b = 215;
	}
	else if ((y > pad && y < (e->page.height - pad))
	&& (x == pad || x == (e->page.width - pad)))
	{
		e->page.bg_color.r = 215;
		e->page.bg_color.g = 215;
		e->page.bg_color.b = 215;
	}
	else
	{
		e->page.bg_color.r = e->page.new_color.r;
		e->page.bg_color.g = e->page.new_color.g;
		e->page.bg_color.b = e->page.new_color.b;
	}
}

void	ft_sidebar_gradient(t_env *e, int x)
{
	if (x == e->sidebar.x)
	{
		e->sidebar.sb_color.r = 200;
		e->sidebar.sb_color.g = 200;
		e->sidebar.sb_color.b = 200;
	}
	else if (x > e->sidebar.x && x < (e->sidebar.x + 25))
	{
		e->sidebar.sb_color.r++;
		e->sidebar.sb_color.g++;
		e->sidebar.sb_color.b++;
	}
	else
	{
		e->sidebar.sb_color.r = 225;
		e->sidebar.sb_color.g = 225;
		e->sidebar.sb_color.b = 225;
	}
}

void	ft_boxes_padding(t_env *e, int x, int y)
{
	int		pad;

	pad = e->box.padding;
	if ((x >= (e->box.x + pad) && x <= (e->box.x1 - pad))
	&& (y == (e->box.y + pad) || y == (e->box.y1 - pad)) && x % 4 != 0)
	{
		e->box.elem_color.r = 15;
		e->box.elem_color.g = 15;
		e->box.elem_color.b = 15;
	}
	else if ((y > (e->box.y + pad) && y < (e->box.y1 - pad))
	&& (x == (e->box.x + pad) || x == (e->box.x1 - pad)) && y % 4 != 0)
	{
		e->box.elem_color.r = 15;
		e->box.elem_color.g = 15;
		e->box.elem_color.b = 15;
	}
	else
	{
		if (e->page.bg_color.r == 75 && e->page.bg_color.g == 115
		&& e->page.bg_color.b == 190)
		{
			e->box.elem_color.r = 245;
			e->box.elem_color.g = 245;
			e->box.elem_color.b = 245;
		}
		else
		{
			e->box.elem_color.r = 205;
			e->box.elem_color.g = 220;
			e->box.elem_color.b = 245;
		}
	}
}

void	ft_boxes_margin(t_env *e)
{
	int		x;
	int		y;
	int		x1;
	int		y1;

	x = e->box.x - e->box.margin;
	y = e->box.y - e->box.margin;
	x1 = e->box.x1 + e->box.margin;
	y1 = e->box.y1 + e->box.margin;
	while (y <= y1)
	{
		while (x <= x1)
		{
			if ((x >= (e->box.x - e->box.margin) && x <= (e->box.x1 + e->box.margin))
			&& (y == (e->box.y - e->box.margin) || y == (e->box.y1 + e->box.margin))
			&& x % 4 != 0)
				ft_display(e, &e->box.elem_color, x, y);
			else if ((y >= (e->box.y - e->box.margin) && y <= (e->box.y1 + e->box.margin))
			&& (x == (e->box.x - e->box.margin) || x == (e->box.x1 + e->box.margin))
			&& y % 4 != 0)
				ft_display(e, &e->box.elem_color, x, y);
			x++;
		}
		x = e->box.x - e->box.margin;
		y++;
	}
}

void	ft_color_palette(t_env *e, int i)
{
	if (i == 0)
	{
		e->palette. r = 51;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 1)
	{
		e->palette. r = 51;
		e->palette. g = 25;
		e->palette. b = 0;
	}
		if (i == 2)
	{
		e->palette. r = 51;
		e->palette. g = 51;
		e->palette. b = 0;
	}
		if (i == 3)
	{
		e->palette. r = 25;
		e->palette. g = 51;
		e->palette. b = 0;
	}
		if (i == 4)
	{
		e->palette. r = 0;
		e->palette. g = 51;
		e->palette. b = 0;
	}
		if (i == 5)
	{
		e->palette. r = 0;
		e->palette. g = 51;
		e->palette. b = 25;
	}
		if (i == 6)
	{
		e->palette. r = 0;
		e->palette. g = 51;
		e->palette. b = 51;
	}
		if (i == 7)
	{
		e->palette. r = 0;
		e->palette. g = 25;
		e->palette. b = 51;
	}
		if (i == 8)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 51;
	}
		if (i == 9)
	{
		e->palette. r = 25;
		e->palette. g = 0;
		e->palette. b = 51;
	}
		if (i == 10)
	{
		e->palette. r = 51;
		e->palette. g = 0;
		e->palette. b = 51;
	}
		if (i == 11)
	{
		e->palette. r = 51;
		e->palette. g = 0;
		e->palette. b = 25;
	}
		if (i == 12)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 13)
	{
		e->palette. r = 102;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 14)
	{
		e->palette. r = 102;
		e->palette. g = 51;
		e->palette. b = 0;
	}
		if (i == 15)
	{
		e->palette. r = 102;
		e->palette. g = 102;
		e->palette. b = 0;
	}
		if (i == 16)
	{
		e->palette. r = 51;
		e->palette. g = 102;
		e->palette. b = 0;
	}
		if (i == 17)
	{
		e->palette. r = 0;
		e->palette. g = 102;
		e->palette. b = 0;
	}
		if (i == 18)
	{
		e->palette. r = 0;
		e->palette. g = 102;
		e->palette. b = 51;
	}
		if (i == 19)
	{
		e->palette. r = 0;
		e->palette. g = 102;
		e->palette. b = 102;
	}
		if (i == 20)
	{
		e->palette. r = 0;
		e->palette. g = 51;
		e->palette. b = 102;
	}
		if (i == 21)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 102;
	}
		if (i == 22)
	{
		e->palette. r = 51;
		e->palette. g = 0;
		e->palette. b = 102;
	}
		if (i == 23)
	{
		e->palette. r = 102;
		e->palette. g = 0;
		e->palette. b = 102;
	}
		if (i == 24)
	{
		e->palette. r = 102;
		e->palette. g = 0;
		e->palette. b = 51;
	}
		if (i == 25)
	{
		e->palette. r = 32;
		e->palette. g = 32;
		e->palette. b = 32;
	}
		if (i == 26)
	{
		e->palette. r = 153;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 27)
	{
		e->palette. r = 153;
		e->palette. g = 76;
		e->palette. b = 0;
	}
		if (i == 28)
	{
		e->palette. r = 153;
		e->palette. g = 153;
		e->palette. b = 0;
	}
		if (i == 29)
	{
		e->palette. r = 76;
		e->palette. g = 153;
		e->palette. b = 0;
	}
		if (i == 30)
	{
		e->palette. r = 0;
		e->palette. g = 153;
		e->palette. b = 0;
	}
		if (i == 31)
	{
		e->palette. r = 0;
		e->palette. g = 153;
		e->palette. b = 76;
	}
		if (i == 32)
	{
		e->palette. r = 0;
		e->palette. g = 153;
		e->palette. b = 153;
	}
		if (i == 33)
	{
		e->palette. r = 0;
		e->palette. g = 76;
		e->palette. b = 153;
	}
		if (i == 34)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 153;
	}
		if (i == 35)
	{
		e->palette. r = 76;
		e->palette. g = 0;
		e->palette. b = 153;
	}
		if (i == 36)
	{
		e->palette. r = 153;
		e->palette. g = 0;
		e->palette. b = 153;
	}
		if (i == 37)
	{
		e->palette. r = 153;
		e->palette. g = 0;
		e->palette. b = 76;
	}
		if (i == 38)
	{
		e->palette. r = 64;
		e->palette. g = 64;
		e->palette. b = 64;
	}
		if (i == 39)
	{
		e->palette. r = 204;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 40)
	{
		e->palette. r = 204;
		e->palette. g = 102;
		e->palette. b = 0;
	}
		if (i == 41)
	{
		e->palette. r = 204;
		e->palette. g = 204;
		e->palette. b = 0;
	}
		if (i == 42)
	{
		e->palette. r = 102;
		e->palette. g = 204;
		e->palette. b = 0;
	}
		if (i == 43)
	{
		e->palette. r = 0;
		e->palette. g = 204;
		e->palette. b = 0;
	}
		if (i == 44)
	{
		e->palette. r = 0;
		e->palette. g = 204;
		e->palette. b = 102;
	}
		if (i == 45)
	{
		e->palette. r = 0;
		e->palette. g = 204;
		e->palette. b = 204;
	}
		if (i == 46)
	{
		e->palette. r = 0;
		e->palette. g = 102;
		e->palette. b = 204;
	}
		if (i == 47)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 204;
	}
		if (i == 48)
	{
		e->palette. r = 102;
		e->palette. g = 0;
		e->palette. b = 204;
	}
		if (i == 49)
	{
		e->palette. r = 204;
		e->palette. g = 0;
		e->palette. b = 204;
	}
		if (i == 50)
	{
		e->palette. r = 204;
		e->palette. g = 0;
		e->palette. b = 102;
	}
		if (i == 51)
	{
		e->palette. r = 96;
		e->palette. g = 96;
		e->palette. b = 96;
	}
		if (i == 52)
	{
		e->palette. r = 255;
		e->palette. g = 0;
		e->palette. b = 0;
	}
		if (i == 53)
	{
		e->palette. r = 255;
		e->palette. g = 128;
		e->palette. b = 0;
	}
		if (i == 54)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 0;
	}
		if (i == 55)
	{
		e->palette. r = 128;
		e->palette. g = 255;
		e->palette. b = 0;
	}
		if (i == 56)
	{
		e->palette. r = 0;
		e->palette. g = 255;
		e->palette. b = 0;
	}
		if (i == 57)
	{
		e->palette. r = 0;
		e->palette. g = 255;
		e->palette. b = 128;
	}
		if (i == 58)
	{
		e->palette. r = 0;
		e->palette. g = 255;
		e->palette. b = 255;
	}
		if (i == 59)
	{
		e->palette. r = 0;
		e->palette. g = 128;
		e->palette. b = 255;
	}
		if (i == 60)
	{
		e->palette. r = 0;
		e->palette. g = 0;
		e->palette. b = 255;
	}
		if (i == 61)
	{
		e->palette. r = 128;
		e->palette. g = 0;
		e->palette. b = 255;
	}
		if (i == 62)
	{
		e->palette. r = 255;
		e->palette. g = 0;
		e->palette. b = 255;
	}
		if (i == 63)
	{
		e->palette. r = 255;
		e->palette. g = 0;
		e->palette. b = 128;
	}
		if (i == 64)
	{
		e->palette. r = 128;
		e->palette. g = 128;
		e->palette. b = 128;
	}
		if (i == 65)
	{
		e->palette. r = 255;
		e->palette. g = 51;
		e->palette. b = 51;
	}
		if (i == 66)
	{
		e->palette. r = 255;
		e->palette. g = 153;
		e->palette. b = 51;
	}
		if (i == 67)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 51;
	}
		if (i == 68)
	{
		e->palette. r = 153;
		e->palette. g = 255;
		e->palette. b = 51;
	}
		if (i == 69)
	{
		e->palette. r = 51;
		e->palette. g = 255;
		e->palette. b = 51;
	}
		if (i == 70)
	{
		e->palette. r = 51;
		e->palette. g = 255;
		e->palette. b = 153;
	}
		if (i == 71)
	{
		e->palette. r = 51;
		e->palette. g = 255;
		e->palette. b = 255;
	}
		if (i == 72)
	{
		e->palette. r = 51;
		e->palette. g = 153;
		e->palette. b = 255;
	}
		if (i == 73)
	{
		e->palette. r = 51;
		e->palette. g = 51;
		e->palette. b = 255;
	}
		if (i == 74)
	{
		e->palette. r = 153;
		e->palette. g = 51;
		e->palette. b = 255;
	}
		if (i == 75)
	{
		e->palette. r = 255;
		e->palette. g = 51;
		e->palette. b = 255;
	}
		if (i == 76)
	{
		e->palette. r = 255;
		e->palette. g = 51;
		e->palette. b = 153;
	}
		if (i == 77)
	{
		e->palette. r = 160;
		e->palette. g = 160;
		e->palette. b = 160;
	}
		if (i == 78)
	{
		e->palette. r = 255;
		e->palette. g = 102;
		e->palette. b = 102;
	}
		if (i == 79)
	{
		e->palette. r = 255;
		e->palette. g = 178;
		e->palette. b = 102;
	}
		if (i == 80)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 102;
	}
		if (i == 81)
	{
		e->palette. r = 178;
		e->palette. g = 255;
		e->palette. b = 102;
	}
		if (i == 82)
	{
		e->palette. r = 102;
		e->palette. g = 255;
		e->palette. b = 102;
	}
		if (i == 83)
	{
		e->palette. r = 102;
		e->palette. g = 255;
		e->palette. b = 178;
	}
		if (i == 84)
	{
		e->palette. r = 102;
		e->palette. g = 255;
		e->palette. b = 255;
	}
		if (i == 85)
	{
		e->palette. r = 102;
		e->palette. g = 178;
		e->palette. b = 255;
	}
		if (i == 86)
	{
		e->palette. r = 102;
		e->palette. g = 102;
		e->palette. b = 255;
	}
		if (i == 87)
	{
		e->palette. r = 178;
		e->palette. g = 102;
		e->palette. b = 255;
	}
		if (i == 88)
	{
		e->palette. r = 255;
		e->palette. g = 102;
		e->palette. b = 255;
	}
		if (i == 89)
	{
		e->palette. r = 255;
		e->palette. g = 102;
		e->palette. b = 178;
	}
		if (i == 90)
	{
		e->palette. r = 192;
		e->palette. g = 192;
		e->palette. b = 192;
	}
		if (i == 91)
	{
		e->palette. r = 255;
		e->palette. g = 153;
		e->palette. b = 153;
	}
		if (i == 92)
	{
		e->palette. r = 255;
		e->palette. g = 204;
		e->palette. b = 153;
	}
		if (i == 93)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 153;
	}
		if (i == 94)
	{
		e->palette. r = 204;
		e->palette. g = 255;
		e->palette. b = 153;
	}
		if (i == 95)
	{
		e->palette. r = 153;
		e->palette. g = 255;
		e->palette. b = 153;
	}
		if (i == 96)
	{
		e->palette. r = 153;
		e->palette. g = 255;
		e->palette. b = 204;
	}
		if (i == 97)
	{
		e->palette. r = 153;
		e->palette. g = 255;
		e->palette. b = 255;
	}
		if (i == 98)
	{
		e->palette. r = 153;
		e->palette. g = 204;
		e->palette. b = 255;
	}
		if (i == 99)
	{
		e->palette. r = 153;
		e->palette. g = 153;
		e->palette. b = 255;
	}
		if (i == 100)
	{
		e->palette. r = 204;
		e->palette. g = 153;
		e->palette. b = 255;
	}
		if (i == 101)
	{
		e->palette. r = 255;
		e->palette. g = 153;
		e->palette. b = 255;
	}
		if (i == 102)
	{
		e->palette. r = 255;
		e->palette. g = 153;
		e->palette. b = 204;
	}
		if (i == 103)
	{
		e->palette. r = 224;
		e->palette. g = 224;
		e->palette. b = 224;
	}
		if (i == 104)
	{
		e->palette. r = 255;
		e->palette. g = 204;
		e->palette. b = 204;
	}
		if (i == 105)
	{
		e->palette. r = 255;
		e->palette. g = 229;
		e->palette. b = 204;
	}
		if (i == 106)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 204;
	}
		if (i == 107)
	{
		e->palette. r = 229;
		e->palette. g = 255;
		e->palette. b = 204;
	}
		if (i == 108)
	{
		e->palette. r = 204;
		e->palette. g = 255;
		e->palette. b = 204;
	}
		if (i == 109)
	{
		e->palette. r = 204;
		e->palette. g = 255;
		e->palette. b = 229;
	}
		if (i == 110)
	{
		e->palette. r = 204;
		e->palette. g = 255;
		e->palette. b = 255;
	}
		if (i == 111)
	{
		e->palette. r = 204;
		e->palette. g = 229;
		e->palette. b = 255;
	}
		if (i == 112)
	{
		e->palette. r = 204;
		e->palette. g = 204;
		e->palette. b = 255;
	}
		if (i == 113)
	{
		e->palette. r = 229;
		e->palette. g = 204;
		e->palette. b = 255;
	}
		if (i == 114)
	{
		e->palette. r = 255;
		e->palette. g = 204;
		e->palette. b = 204;
	}
		if (i == 115)
	{
		e->palette. r = 255;
		e->palette. g = 204;
		e->palette. b = 229;
	}
		if (i == 116)
	{
		e->palette. r = 255;
		e->palette. g = 255;
		e->palette. b = 255;
	}
}
