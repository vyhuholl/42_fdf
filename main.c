/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 21:59:43 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/19 20:49:30 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*ft_init_fdf(t_map *map, char *title)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf*)ft_memalloc(sizeof(t_fdf))))
		ft_error("FdF initialization error");
	if (!(fdf->mlx = mlx_init()))
		ft_error("Mlx initialization error");
	if (!(fdf->window = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
		ft_error("New window initialization error");
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT)))
		ft_error("New image initialization error");
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
										&(fdf->size_line), &(fdf->end));
	fdf->map = map;
	return (fdf);
}

int		ft_key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	if (keycode == ESCAPE_KEY)
	{
		(void)param;
		exit(0);
	}
	else if (keycode >= 123 && keycode <= 126)
	{
		if (keycode == UP_KEY)
			fdf->map->delta_y -= 10;
		else if (keycode == DOWN_KEY)
			fdf->map->delta_y += 10;
		else if (keycode == LEFT_KEY)
			fdf->map->delta_x += 10;
		else if (keycode == RIGHT_KEY)
			fdf->map->delta_x -= 10;
		ft_redraw_map(fdf);
	}
	return (0);
}

void	ft_redraw_map(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT)))
	{
		(void)fdf;
		ft_error("New image initialization error");
	}
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
										&(fdf->size_line), &(fdf->end));
	ft_draw_map(fdf);
}

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int		main(int argc, char **argv)
{
	char	**lines;
	t_map	*map;
	t_fdf	*fdf;

	errno = 0;
	if (argc == 2)
	{
		ft_read_file(argv[1], &lines);
		map = ft_init_map(lines);
		ft_read_map(map, lines);
		fdf = ft_init_fdf(map, argv[1]);
		ft_draw_map(fdf);
		mlx_key_hook(fdf->window, ft_key_hook, fdf);
		mlx_loop(fdf->mlx);
	}
	else
		ft_putstr("Usage: ./fdf map_file\n");
	return (0);
}
