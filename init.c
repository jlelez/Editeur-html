/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 14:58:45 by afouchar          #+#    #+#             */
/*   Updated: 2015/02/26 20:51:18 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

void	ft_init_layout(t_env *e)
{
	e->page.width = 596;
	e->page.height = 842;
	e->page.padding_mm = 12;
	e->page.padding = ft_mmtopx(e->page.padding_mm);
	e->page.bg_color.r = 255;
	e->page.bg_color.g = 255;
	e->page.bg_color.b = 255;
	e->page.new_color.r = 255;
	e->page.new_color.g = 255;
	e->page.new_color.b = 255;
}

void	ft_init_select(t_env *e)
{
	e->select.x = 0;
	e->select.y = 0;
	e->select.x1 = 0;
	e->select.y1 = 0;
	e->select.width = 0;
	e->select.height = 0;
	e->select.margin = 2;
	e->select.padding = 8;
	e->select.select_color.r = 75;
	e->select.select_color.g = 115;
	e->select.select_color.b = 190;
	e->box.align = 0;
	e->box.x = 0;
	e->box.y = 0;
	e->box.x1 = 0;
	e->box.y1 = 0;
	e->box.width = 0;
	e->box.height = 0;
	e->box.content = NULL;
	e->box.margin_mm = 3;
	e->box.margin = ft_mmtopx(3);
	e->box.padding_mm = 1;
	e->box.padding = ft_mmtopx(1);
	e->box.font_size = 12;
	e->box.elem_color.r = 205;
	e->box.elem_color.g = 220;
	e->box.elem_color.b = 245;
}

void	ft_init_env(t_env *e, char *prog_name)
{
	e->prog_name = ft_strdup(prog_name + 2);
	e->width = 596 + 256;
	e->height = 842;
	if ((e->mlx = mlx_init()) == NULL)
		exit(0);
	e->win = mlx_new_window(e->mlx, e->width, e->height, e->prog_name);
	e->html.iweb = 0;
	e->html.fd_write = 0;
	e->html.fd_writecss = 0;
	e->nb_div = 0;
	e->file_saved = 0;
	e->new_list = 0;
	e->tabindex = 4;
	e->drag = 0;
	e->drag_file = 0;
	e->magnet = 1;
	e->move = 0;
	e->move_box.x = 0;
	e->move_box.y = 0;
	e->coord = NULL;
	e->newlist = NULL;
	e->palette.r = 0;
	e->palette.g = 0;
	e->palette.b = 0;
	e->drop_file.x = 0;
	e->drop_file.x1 = 0;
	e->drop_file.y = 0;
	e->drop_file.y1 = 0;
	e->html_name = ft_strdup("layout.html");
	e->html_name = ft_set_new_file_name(e->html_name);
	e->css_name = ft_strdup("style.css");
	e->css_name = ft_set_new_file_name(e->css_name);
	ft_init_font_family(e);
	ft_init_select(e);
	ft_init_sidebar(e);
	ft_init_button(e);
	ft_get_files(e);
}

void	ft_init_sidebar(t_env *e)
{
	e->sidebar.x = 596;
	e->sidebar.x1 = e->width;
	e->sidebar.y = 0;
	e->sidebar.y1 = e->height;
	e->sidebar.sb_color.r = 225;
	e->sidebar.sb_color.g = 225;
	e->sidebar.sb_color.b = 225;
	e->sidebar.txt_color = 0x252525;
	e->sidebar.lines.r = 95;
	e->sidebar.lines.g = 95;
	e->sidebar.lines.b = 95;
}

void	ft_init_button(t_env *e)
{
	e->button.x = e->sidebar.x1 - 40;
	e->button.x1 = e->sidebar.x1 - 20;
	e->button.y = 20;
	e->button.y1 = 40;

	e->button.b_color.r = 130;
	e->button.b_color.g = 130;
	e->button.b_color.b = 130;
}

void	ft_init_font_family(t_env *e)
{
	e->tabfont_family = (char**)malloc(sizeof(char*) * 15);
	e->tabfont_family[0] = ft_strdup("Goergia");
	e->tabfont_family[1] = ft_strdup("Palatino Linotype");
	e->tabfont_family[2] = ft_strdup("Book Antiqua");
	e->tabfont_family[3] = ft_strdup("Times New Roman");
	e->tabfont_family[4] = ft_strdup("Arial");
	e->tabfont_family[5] = ft_strdup("Helvetica");
	e->tabfont_family[6] = ft_strdup("Arial Black");
	e->tabfont_family[7] = ft_strdup("Impact");
	e->tabfont_family[8] = ft_strdup("Lucida Sans Unicode");
	e->tabfont_family[9] = ft_strdup("Tahoma");
	e->tabfont_family[10] = ft_strdup("Verdana");
	e->tabfont_family[11] = ft_strdup("Courier New");
	e->tabfont_family[12] = ft_strdup("Lucida Console");
	e->tabfont_family[13] = ft_strdup("initial");
	e->tabfont_family[14] = NULL;
}
