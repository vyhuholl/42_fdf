/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 23:27:49 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/19 21:11:45 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_read_file(char *filename, char ***lines)
{
	char	buf[BUFF_SIZE + 1];
	char	*line;
	char	*temp;
	int		ret;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("Invalid map file");
	line = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			ft_error("Map reading error");
		buf[ret] = '\0';
		temp = line;
		line = ft_strjoin(temp, buf);
		ft_strdel(&temp);
	}
	ft_strlen(line) == 0 ? ft_error("Empty map") : 0;
	*lines = ft_strsplit(line, '\n');
	ft_strdel(&line);
}

t_point	*ft_init_point(t_map *map, int x, int y, char **line)
{
	t_point	*p;

	p = ft_memalloc(sizeof(t_point));
	if (p == NULL || ft_is_number(line[x]) == -1)
		ft_error("Invalid value or memory error");
	p->x = x;
	p->y = y;
	p->z = ft_atoi(line[x]);
	if (p->z < map->z_min)
		map->z_min = p->z;
	if (p->z > map->z_max)
		map->z_max = p->z;
	return (p);
}

t_map	*ft_init_map(char **lines)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		ft_error("Memory allocation error");
	map->x = ft_word_count(lines[0], ' ');
	map->y = 0;
	while (lines[map->y])
		if (ft_word_count(lines[(map->y)++], ' ') != map->x)
			ft_error("Invalid map");
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->delta_x = 0;
	map->delta_y = 0;
	if (WIN_WIDTH / (2 * map->y) < WIN_HEIGHT / (2 * map->x))
		map->scale = WIN_WIDTH / map->y;
	else
		map->scale = WIN_HEIGHT / map->x;
	map->coord = ft_memalloc(sizeof(t_point *) * map->x * map->y);
	if (map->coord == NULL)
		ft_error("Memory allocation error");
	return (map);
}

void	ft_read_map(t_map *map, char **lines)
{
	char	**line;
	int		x;
	int		y;

	y = 0;
	while (y < map->y)
	{
		line = ft_strsplit(lines[y], ' ');
		x = 0;
		while (x < map->x)
		{
			map->coord[map->x * y + x] = ft_init_point(map, x, y, line);
			if (map->coord[map->x * y + x] == NULL)
				ft_error("Invalid value or memory error");
			x++;
		}
		ft_free_lines(&line);
		y++;
	}
	if (map->z_max > map->z_min)
		map->z = map->z_max - map->z_min;
	else
		map->z = map->z_min - map->z_max;
	ft_free_lines(&lines);
}
