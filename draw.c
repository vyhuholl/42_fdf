/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 06:53:42 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/19 22:02:41 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_point(t_fdf *fdf, t_point p, int color)
{
	int	i;

	if (p.x >= 0 && p.x < WIN_WIDTH && p.y >= 0 && p.y < WIN_HEIGHT)
	{
		i = (p.x * fdf->bits_per_pixel / 8) + (p.y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

t_point	ft_iso(t_map *map, t_point p)
{
	int		x_old;
	int		y_old;

	p.x *= map->scale;
	p.y *= map->scale;
	p.z *= map->scale;
	if (map->z != 0)
		p.z /= map->z;
	p.x += map->delta_x;
	p.y += map->delta_y;
	p.x -= (map->x * map->scale) / 2;
	p.y -= (map->y * map->scale) / 2;
	x_old = p.x;
	y_old = p.y;
	p.x = (x_old - y_old) * cos(0.523599);
	p.y = -p.z + (x_old + y_old) * sin(0.523599);
	p.x += (WIN_WIDTH + map->x * map->scale) / 4;
	p.y += (WIN_HEIGHT + map->y * map->scale) / 4;
	return (p);
}

void	ft_draw_line(t_fdf *fdf, t_point p_1, t_point p_2)
{
	t_point	delta;
	t_point	sign;
	t_point	curr;
	int		error[2];

	delta.x = p_1.x > p_2.x ? p_1.x - p_2.x : p_2.x - p_1.x;
	delta.y = p_1.y > p_2.y ? p_1.y - p_2.y : p_2.y - p_1.y;
	sign.x = p_1.x < p_2.x ? 1 : -1;
	sign.y = p_1.y < p_2.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	curr = p_1;
	while (curr.x != p_2.x || curr.y != p_2.y)
	{
		ft_draw_point(fdf, curr, LINE_COLOR);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			curr.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			curr.y += sign.y;
		}
	}
}

void	ft_draw_wireframe(t_fdf *fdf, t_map *map)
{
	t_point	p;
	int		x;
	int		y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			p = ft_iso(map, *map->coord[map->x * y + x]);
			ft_draw_point(fdf, p, POINT_COLOR);
			if (y != map->y - 1)
				ft_draw_line(fdf, ft_iso(map, *map->coord[map->x * y + x]),
				ft_iso(map, *map->coord[map->x * (y + 1) + x]));
			if (x != map->x - 1)
				ft_draw_line(fdf, ft_iso(map, *map->coord[map->x * y + x]),
				ft_iso(map, *map->coord[map->x * y + x + 1]));
			x++;
		}
		y++;
	}
}

void	ft_draw_map(t_fdf *fdf)
{
	t_point	p;
	int		*img;
	int		i;

	ft_bzero(fdf->data_addr,
	WIN_WIDTH * WIN_HEIGHT * (fdf->bits_per_pixel / 8));
	p.x = WIN_WIDTH / 2;
	p.y = WIN_HEIGHT / 2;
	img = (int*)fdf->data_addr;
	i = -1;
	while (++i < WIN_WIDTH * WIN_HEIGHT)
		img[i] = BACKGROUND_COLOR;
	if (fdf->map->x == 1 && fdf->map->y == 1)
		ft_draw_point(fdf, p, POINT_COLOR);
	else
		ft_draw_wireframe(fdf, fdf->map);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_string_put(fdf->mlx, fdf->window, 50, 30,
	TEXT_COLOR, "Use arrows to move");
	mlx_string_put(fdf->mlx, fdf->window, 50, 60,
	TEXT_COLOR, "Press Escape to quit");
}
