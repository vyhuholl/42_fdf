/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <sghezn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 05:25:56 by sghezn            #+#    #+#             */
/*   Updated: 2020/04/19 20:48:42 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "libft/libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUFF_SIZE 1024
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define POINT_COLOR 0X00E5EE
# define LINE_COLOR 0XFF3E96
# define TEXT_COLOR 0XC0D6E4
# define BACKGROUND_COLOR 0X8A2BE2

# define ESCAPE_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 124
# define RIGHT_KEY 123

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef struct		s_map
{
	int				x;
	int				y;
	int				z;
	int				z_min;
	int				z_max;
	int				delta_x;
	int				delta_y;
	int				scale;
	t_point			**coord;
}					t_map;

typedef struct		s_fdf
{
	void			*mlx;
	void			*window;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				end;
	t_map			*map;
}					t_fdf;

void				ft_read_file(char *filename, char ***lines);
t_point				*ft_init_point(t_map *map, int x, int y, char **line);
t_map				*ft_init_map(char **lines);
void				ft_read_map(t_map *map, char **lines);
t_fdf				*ft_init_fdf(t_map *map, char *title);
void				ft_draw_point(t_fdf *fdf, t_point p, int color);
t_point				ft_iso(t_map *map, t_point p);
void				ft_draw_line(t_fdf *fdf, t_point p_1, t_point p_2);
void				ft_draw_wireframe(t_fdf *fdf, t_map *map);
void				ft_draw_map(t_fdf *fdf);
int					ft_key_hook(int keycode, void *param);
void				ft_redraw_map(t_fdf *fdf);
void				ft_error(char *str);
int					ft_is_number(char *s);
int					ft_word_count(char *s, char c);
void				ft_free_lines(char ***lines);

#endif
