#include "layout.h"

void	ft_ui(t_env *e)
{
	int		x;
	int		y;
	int		y1;
	int		i;
	int		plus;

	x = e->button.x;
	y = e->button.y;
	y1 = e->button.y1;
	i = 0;
	plus = 0;
	while (i < 3)
	{
		plus = 0;
		while (y <= y1)
		{
			while (x <= e->button.x1)
			{
				ft_display(e, &e->button.b_color, x, y);
				x++;
			}
			x = e->button.x;
			y++;
			plus++;
		}
		y++;
		y1 += plus + 1;
		plus = 0;
	        while (y <= y1)
		{
			while (x <= e->button.x1)
			{
				ft_display(e, &e->button.b_color, x, y);
				x++;
			}
			x = e->button.x;
			y++;
			plus++;
		}
		x = e->button.x;
		y +=4;
		y1 += plus + 4;
		i++;
	}
	ft_ui_names(e);
}

void	ft_ui_names(t_env *e)
{
	int		x;
	int		y;
	int		y1;
	int		ys;
	int		y1s;
	int		i;
	int		plus;
	t_color		c;

	x = e->button.x - 100;
	y = e->button.y;
	y1 = e->button.y1 + 22;
	i = 0;
	while (i < 3)
	{
		c.r = e->button.b_color.r + 10;
		c.g = e->button.b_color.g + 10;
		c.b = e->button.b_color.b + 10;
		y1s = y1;
		ys = y + ((y1 - y) / 2);
		plus = 0;
		while (y <= y1)
		{
			while (x < e->button.x - 5)
			{
				if (y >= ys && y <= y1s)
					ft_display(e, &c, x, y);
				else
					ft_display(e, &e->button.b_color, x, y);
				x++;
			}
			c.r++;
			c.g++;
			c.b++;
			x = e->button.x - 100;
			y++;
			plus++;
		}
		y += 4;
		y1 += plus + 4;
		i++;
	}
}

void	ft_write_ui(t_env *e)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = e->button.x + 8;
	y = e->button.y + 16;
	while (i < 3)
	{
		mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "+");
		y += 20;
		mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "-");
		y += 27;
		i++;
	}
        y = e->button.y + 14;
        x -= 100;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "layout margin");
	y += 22;
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->page.padding_mm));
	x += 24;
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "mm");
	x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->page.padding));
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "px");
	y += 25;

	x -= (24 * 3);
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "box margin");
        y += 22;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->box.margin_mm));
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "mm");
        x += 24;
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->box.margin));
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "px");
	y += 25;

	x -= (24 * 3);
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "box padding");
        y += 22;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->box.padding_mm));
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "mm");
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, ft_itoa(e->box.padding));
        x += 24;
        mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "px");

	x = e->button.x - 161;
	y = e->button.y + 15;
	mlx_string_put(e->mlx, e->win, x, y, 0xE0E0E0, "SAVE");

	x = e->button.x - 176;
	y = e->button.y + 35;
	if (e->magnet == 0)
	{
		x -= 3;
		mlx_string_put(e->mlx, e->win, x, y, 0xE0E0E0, "MAGNET OFF");
	}
	else if (e->magnet == 1)
		mlx_string_put(e->mlx, e->win, x, y, 0xE0E0E0, "MAGNET ON");
}

void	ft_say_saved(t_env *e)
{
	int		x;
	int		y;
//	int		i;

	x = e->button.x - 180;
	y = e->button.y + 68;
//i = 0;
	mlx_string_put(e->mlx, e->win, x, y, e->sidebar.txt_color, "file saved");
}
