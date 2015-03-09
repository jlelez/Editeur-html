/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlelez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 14:43:41 by jlelez            #+#    #+#             */
/*   Updated: 2015/03/05 14:51:28 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

void	ft_html(int fd, t_env *e)
{
	int		fdtext;
	int		ret;
	char	*buff;
	char	*class;

	if (e->nbblock == 0)
	{
		ft_putstr_fd(STARTHTML, fd);
		ft_putstr_fd(e->css_name, fd);
		ft_putstr_fd(STARTHTMLNEXT, fd);
	}
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(DIV, fd);
	class = ft_strjoin(" class=\"div", ft_itoa(e->nb_div));
	class = ft_strjoin(class, "\"");
	ft_putstr_fd(class, fd);
	ft_putchar_fd('>', fd);
	//condition si text ou image pour mettre le txt ou l'image
	if ((ft_strcmp(ft_strrchr(e->content, '.'), ".txt")) == 0)
	{
		e->text = ft_strnew(1);
		buff = (char*)malloc(sizeof(char) * (BUF_SIZE + 1));
		fdtext = open(ft_strjoin(LINKS, e->content), O_RDONLY);
		while ((ret = read(fdtext, buff, BUF_SIZE)) > 0)
		{
			buff[ret] = '\0';
			e->text = ft_strjoin(e->text, buff);
		}
		close(fdtext);
		ft_putstr_fd("<p>", fd);
		ft_putstr_fd(e->text, fd);
		ft_putstr_fd("</p>", fd);
	}
	else
	{
		ft_putstr_fd("\n<img src=\"", fd);
		ft_putstr_fd(ft_strjoin("./", e->content), fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(" height= ", fd);
		ft_putstr_fd(ft_itoa(e->box.height), fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(" width= ", fd);
		ft_putstr_fd(ft_itoa(e->box.width), fd);
		ft_putstr_fd("\"/>\n", fd);
	}
	ft_putstr_fd(DIVEND, fd);
	e->nbblock++;
}

void	ft_css2(int fd, t_env *e)
{
	char	*nameclass;

	nameclass = ft_strjoin(".div", ft_itoa(e->nb_div));
	ft_putstr_fd(nameclass, fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd("\n{\n", fd);
	ft_putstr_fd("position: absolute;\n", fd);
	ft_putstr_fd("overflow: hidden;\n", fd);
	ft_putstr_fd("left: ", fd);
	ft_putstr_fd(ft_itoa(e->box.x), fd);
	ft_putstr_fd("px;\n", fd);
	ft_putstr_fd("top: ", fd);
	ft_putstr_fd(ft_itoa(e->box.y), fd);
	ft_putstr_fd("px;\n", fd);
	ft_putstr_fd("\n}\n", fd);
	e->nb_div++;
}

void	ft_css(int fd, t_env *e)
{
	char	*width;
	char	*height;
	char	*nameclass;

	if (e->nb_div == 0)
	{
		ft_putstr_fd("html\n{\nbackground-color: white;\n}\n\n", fd);
		ft_putstr_fd("body\n{\nwidth: 596px;\nheight: 842px;\n", fd);
		ft_putstr_fd("background-color: rgb(", fd);
		ft_putstr_fd(ft_itoa(e->page.bg_color.r), fd);
		ft_putstr_fd(", ", fd);
		ft_putstr_fd(ft_itoa(e->page.bg_color.g), fd);
		ft_putstr_fd(", ", fd);
		ft_putstr_fd(ft_itoa(e->page.bg_color.b), fd);
		ft_putstr_fd(");", fd);
		ft_putstr_fd("border: 1px solid black;\n}\n\n", fd);
	}
	nameclass = ft_strjoin(".div", ft_itoa(e->nb_div));
	ft_putstr_fd(nameclass, fd);
	if ((ft_strcmp(ft_strrchr(e->content, '.'), ".txt")) == 0)
	{
		ft_putstr_fd(" p\n", fd);
		ft_putstr_fd("{\n", fd);
		width = ft_strjoin(WIDTH, ft_itoa(e->box.width));
		width = ft_strjoin(width, PX);
		height = ft_strjoin(HEIGHT, ft_itoa(e->box.height));
		height = ft_strjoin(height, PX);
		ft_putstr_fd(width, fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd(height, fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd("\ntext-align: ", fd);
		if (e->box.align == 0)
			ft_putstr_fd("left;\n", fd);
		if (e->box.align == 1)
			ft_putstr_fd("center;\n", fd);
		if (e->box.align == 2)
			ft_putstr_fd("right;\n", fd);
		ft_putstr_fd("\nfont-size: ", fd);
		ft_putstr_fd(ft_itoa(e->box.font_size), fd);
		ft_putstr_fd("px;\n", fd);
		ft_putstr_fd("\nfont-family: ", fd);
		ft_putstr_fd((e->tabfont_family[e->tabindex]), fd);
		ft_putstr_fd(";\n", fd);
		ft_putstr_fd("word-wrap: break-word;", fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd("overflow: hidden;\n", fd);
		ft_putstr_fd("\n}\n\n", fd);
	}
	else
	{
		ft_putstr_fd(" img\n", fd);
		ft_putstr_fd("{\n", fd);
		ft_putstr_fd("display: block;\n", fd);
		ft_putstr_fd("width: ", fd);
		ft_putstr_fd(ft_itoa(e->box.width), fd);
		ft_putstr_fd(";\n", fd);
		ft_putstr_fd("height: ", fd);
		ft_putstr_fd(ft_itoa(e->box.height), fd);
		ft_putstr_fd(";\n", fd);
		ft_putstr_fd("overflow: hidden;\n", fd);
		ft_putstr_fd("}\n", fd);
	}
	ft_css2(fd, e);
}

void	ft_save(t_env *e)
{
	t_list	*tmp;
	char	*html_path;
	char	*css_path;

	tmp = e->coord;
	html_path = ft_strjoin(LINKS, e->html_name);
	css_path = ft_strjoin(LINKS, e->css_name);
	if (ft_exist(LINKS, e->html_name) == 1)
		remove(html_path);
	if (ft_exist(LINKS, e->css_name) == 1)
		remove(css_path);
	if ((e->html.fd_write = open(html_path, O_WRONLY | O_CREAT | O_EXCL, 0666)) > 0
			&& (e->html.fd_writecss = open(css_path, O_WRONLY | O_CREAT | O_EXCL, 0666)) > 0)
	{
		while (tmp)
		{
			e->box.width = ((t_box*)(tmp->content))->x1
				- ((t_box*)(tmp->content))->x;
			e->box.height = ((t_box*)(tmp->content))->y1
				- ((t_box*)(tmp->content))->y;
			e->box.x = ((t_box*)(tmp->content))->x;
			e->box.y = ((t_box*)(tmp->content))->y;
			e->box.x1 = ((t_box*)(tmp->content))->x1;
			e->box.y1 = ((t_box*)(tmp->content))->y1;
			e->box.padding = ((t_box*)(tmp->content))->padding;
			e->box.margin = ((t_box*)(tmp->content))->margin;
			e->box.font_size = ((t_box*)(tmp->content))->font_size;
			e->box.align = ((t_box*)(tmp->content))->align;
			e->content = ft_strdup(((t_box*)(tmp->content))->content);	
			ft_html(e->html.fd_write, e);
			ft_css(e->html.fd_writecss, e);
			tmp = tmp->next;
		}
		ft_putstr_fd(ENDHTML, e->html.fd_write);
		ft_putstr("file saved\n");
		e->nbblock = 0;
		close(e->html.fd_write);
		close(e->html.fd_writecss);
	}
}
