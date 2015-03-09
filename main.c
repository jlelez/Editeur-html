/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afouchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 13:04:33 by afouchar          #+#    #+#             */
/*   Updated: 2015/02/24 16:08:42 by jlelez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "layout.h"

int		main(int argc, char **argv)
{
	t_env	e;

	if (argc == 2)
	{
		//open saved file.layout
		//init structs
	}
	else if (argc == 1)
	{
		ft_init_layout(&e);
	}
	else
	{
		ft_putendl("Too many arguments.");
		return (0);
	}
	ft_init_env(&e, argv[0]);
	mlx_key_hook(e.win, key_hook, &e);

	mlx_mouse_hook(e.win, mouse_press, &e);

	mlx_hook(e.win, 6, (1L << 8), mouse_hook, &e);
	mlx_hook(e.win, 5, (1L << 3), mouse_release, &e);
	mlx_loop_hook(e.mlx, expose_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
