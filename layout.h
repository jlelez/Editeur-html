/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 13:04:56 by afouchar          #+#    #+#             */
/*   Updated: 2015/02/26 20:24:50 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAYOUT_H
# define LAYOUT_H

# include "./libft/libft.h"
# include <mlx.h>
# include </opt/X11/include/X11/X.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

# define STARTHTML "<!DOCTYPE HTML>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<link rel=\"stylesheet\" href=\""
# define STARTHTMLNEXT "\" />\n<title>Title of the document</title>\n</head>\n<body>\n"
# define ENDHTML "\n</body>\n</html>\n"
# define DIV "<div"
# define DIVEND "</div>"
# define WIDTH "width: "
# define HEIGHT "height: "
# define PX "px;"

# define BUF_SIZE 1024
# define RGB (256 * 256 * (int)(c->r) + 256 * (int)(c->g) + (int)(c->b))
# define LINKS "./links/"
# define ESC 65307

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_select
{
	char			*content;
	int			width;
	int			height;
	int			x;
	int			x1;
	int			y;
	int			y1;
	int			margin;
	int			padding;
	t_color		elem_color;
	t_color		select_color;
}		t_select;

typedef struct	s_button
{
	int			x;
	int			x1;
	int			y;
	int			y1;
	t_color		b_color;
}				t_button;

typedef struct	s_sidebar
{
	int			x;
	int			x1;
	int			y;
	int			y1;
	t_color		sb_color;
	int			txt_color;
	t_color		lines;
}				t_sidebar;

typedef struct	s_text
{
	t_color		font_color;
	int			font_type;
	int			font_size;
	int			text_align;
	int			text_valign;
}				t_text;

typedef struct	s_box
{
	char		*content;
	char		*font_family;
	int			font_size;
	int			align;
	int			width;
	int			height;
	int			x;
	int			x1;
	int			y;
	int			y1;
	int			margin;
	int			margin_mm;
	int			padding;
	int			padding_mm;
	t_color		elem_color;
}				t_box;

typedef struct	s_page
{
	int			width;
	int			height;
	int			padding;
	int			padding_mm;
	t_color		bg_color;
	t_color		new_color;
}				t_page;

typedef struct	s_html
{
	int			iweb;
	int			fd_write;
	int			fd_writecss;
}			t_html;

typedef struct	s_move
{
	int			x;
	int			y;
	int			x1;
	int			y1;
}			t_move;

typedef struct	s_point
{
	int			x;
	int			y;
	int			x1;
	int			y1;
}				t_point;

typedef struct  s_env
{
	char		*prog_name;
	char		*html_name;
	char		*css_name;
	char		**file_list;
	int			nb_files;
	void		*mlx;
	void		*win;
	void		*img;
	void		*data;
	int			bpp;
	int			end;
	int			sl;
	int			width;
	int			height;
	int			nb_div;
	t_page		page;
	t_sidebar	sidebar;
	t_select	select;
	int			drag;
	int			drag_file;
	int			move;
	int			magnet;
	int			file_saved;
	int			tabindex;
	//rajout pour html utile ?
	////////////////////////
	int			nbblock;
	char		*text;
	char		*content;
	char		**tabfont_family;
	/////////////////////////
	int			new_list;
	t_move			move_box;
	t_move		drop_file;
	t_button	button;
	t_box		box;
	t_html		html;
	t_list		*coord;
	t_list		*newlist;
	t_color		palette;
}			t_env;

//INIT.c
void			ft_init_layout(t_env *e);
void			ft_init_env(t_env *e, char *prog_name);
void			ft_init_sidebar(t_env *e);
void			ft_init_select(t_env *e);
void			ft_init_button(t_env *e);
void			ft_init_font_family(t_env *e);

//DISPLAY.C
void			ft_display(t_env *e, t_color *c, int x, int y);
void			ft_display_layout(t_env *e);
void			ft_display_sidebar(t_env *e);
void			ft_display_files(t_env *e);
void			ft_display_separator(t_env *e);
void			ft_display_selection(t_env *e);
void			ft_display_boxes(t_env *e);
void			ft_display_delete(t_env *e, int x1, int y);
void			ft_display_grab(t_env *e, int x1, int y);
void			ft_display_fontsize(t_env *e, int x, int y);
void			ft_display_palette(t_env *e);
void			ft_display_file_icon(t_env *e);
void			ft_display_save_button(t_env *e);
void			ft_display_all_boxes(t_env *e);
void			ft_display_font_size(t_env *e);
void			ft_display_font_family(t_env *e);
void			ft_display_dropped_name(t_env *e);
void			ft_display_magnet(t_env *e);
void			ft_display_button_font_family(t_env *e);
void			ft_display_button_align(t_env *e, int x, int y1, int align);
int				expose_hook(t_env *e);

//INPUT.C
int				mouse_hook(int x, int y, t_env *e);
int				key_hook(int keycode, t_env *e);
int				mouse_release(int button, int x, int y, t_env *e);
int				mouse_press(int button, int x, int y, t_env *e);

//COLORS.C
void			ft_page_margin(t_env *e, int x, int y);
void			ft_sidebar_gradient(t_env *e, int x);
void			ft_boxes_padding(t_env *e, int x, int y);
void			ft_boxes_margin(t_env *e);
void			ft_color_palette(t_env *e, int i);

//TOOLS.C
int				ft_mmtopx(int nb);
int				*ft_page_bounds(t_env *e, int x, int x1, int y, int y1);
int				*ft_color_picker(t_env *e, int x, int y);
void			ft_swap(int *a, int *b);
void			ft_save_list(t_env *e);
int				ft_rgbtohex(int r, int g, int b);
char			*itoa(int num, char *str, int base);
void			strrev(char *str);
int 			*ft_repulse_first(t_env *e, int x, int y);
int 			*ft_repulse_second(t_env *e, int x, int y);
int			*ft_magnet_right(t_env *e, int x, int y);
int			*ft_magnet_bottom(t_env *e, int x, int y);
int			*ft_magnet_left(t_env *e, int x, int y);
int			*ft_magnet_top(t_env *e, int x, int y);

//FILES.C
void			ft_get_files(t_env *e);
int				ft_sizeof_dir(char *path);
int				ft_exist(char *path, char *name);
char			*ft_drag_file(t_env *e, int y);
char			*ft_set_new_file_name(char *file);

//UI.C
void			ft_ui(t_env *e);
void			ft_ui_names(t_env *e);
void			ft_write_ui(t_env *e);
void			ft_say_saved(t_env *e);

//HTML.C
void			ft_save(t_env *e);
void			ft_css(int fd, t_env *e);
void			ft_css2(int fd, t_env *e);
void			ft_html(int fd, t_env *e);

#endif
