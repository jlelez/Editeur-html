/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 15:34:37 by afouchar          #+#    #+#             */
/*   Updated: 2015/02/25 13:45:04 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

int		ft_sizeof_dir(char *path)
{
	DIR	*dirp;
	struct dirent	*dp;
	int		i;

	i = 0;
	if ((dirp = opendir(path)) == NULL)
		ft_putendl("can't find ./links/ folder!");
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}

void	ft_get_files(t_env *e)
{
	DIR	*dirp;
	struct dirent	*dp;
	int		i;

	i = 0;
	if ((dirp = opendir(LINKS)) == NULL)
		ft_putendl("can't find links folder!");
	e->file_list = (char **)malloc(sizeof(char *) * (ft_sizeof_dir(LINKS)));
	while ((dp = readdir(dirp)) != NULL)
	{
		if (((ft_strcmp(ft_strrchr(dp->d_name, '.'), ".png") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".jpg") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".bmp") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".gif") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".txt") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".jpeg") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".JPG") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".JPEG") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".PNG") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".GIF") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".BMP") == 0)
		|| (ft_strcmp(ft_strrchr(dp->d_name, '.'), ".TXT") == 0))
		&& dp->d_name[0] != '.')
		{

			e->file_list[i] = ft_strdup(dp->d_name);
			i++;
		}
	}
	e->file_list[i] = NULL;
	e->nb_files = (i - 1);
}

int		ft_exist(char *path, char *name)
{
	DIR	*dirp;
	struct dirent	*dp;

	if ((dirp = opendir(path)) == NULL)
	{
		mkdir(LINKS, 0777);
		dirp = opendir(path);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dp->d_name, name) == 0)
			return (1);
	}
	return (0);
}

char	*ft_drag_file(t_env *e, int y)
{
	char	*file;
	int 	i;
	int 	frame;

	i = 0;
	frame = (e->height / 2) - 13;
	while (i <= e->nb_files)
	{
		if ((y > frame) && (y < (frame + 18)))
		{
			file = ft_strdup(e->file_list[i]);
			return (file);
		}
		i++;
		frame += 18;
	}
	return ("none");
}

char	*ft_set_new_file_name(char *file)
{
	int		sub;
	int		i;
	size_t		j;
	char		*nb;
	char		*ext;

	sub = 0;
	i = 0;
	j = 0;
	nb = 0;
	ext = ft_strnew(1);
	if (ft_strcmp(ft_strrchr(file, '.'), ".html") == 0)
	{
		sub = 5;
		ext = ft_strdup(".html");
	}
	else if (ft_strcmp(ft_strrchr(file, '.'), ".css") == 0)
	{
		sub = 4;
		ext = ft_strdup(".css");
	}
	while (ft_exist(LINKS, file) == 1)
	{
		file = ft_strsub(file, 0, ft_strlen(file) - sub);
		while (ft_isdigit(file[j]) == 0 && j < ft_strlen(file))
			j++;
		if (j == ft_strlen(file))
			file = ft_strjoin(file, ft_itoa(i));
		else
		{
			nb = ft_strsub(file, j, ft_strlen(file));
			i = ft_atoi(nb) + 1;
			file = ft_strsub(file, 0, j);
			file = ft_strjoin(file, ft_itoa(i));
			free(nb);
		}
		file = ft_strjoin(file, ext);
	}
	return (file);
}
