/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 09:42:23 by ssar              #+#    #+#             */
/*   Updated: 2021/07/06 09:13:17 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# define ZOOM 0
# define CENTER 0
# define ALT_CASE 0

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_all
{
	int		add;
	int		map_col;
	int		map_row;
	int		x_screen;
	int		y_screen;
	int		**map;
	int		**value;
	int		tabsize;
	int		alloue[3];
	int		space_x;
	int		space_y;
	int		space;
	int		case_size;
	int		higher;
	t_vars	vars;
	t_data	img;
	int		h_g[2];
	int		h_d[2];
	int		b_g[2];
	int		b_d[2];
	int		g;
}			t_all;

int		ft_free_tab_int(int **tab);
int		ft_len_int(int *str);
int		ft_in(char *str, char c);
int		ft_len(char *str);
char	**ft_free_tab(char **tab);
int		ft_atoi(char *str);
int		get_last_line(char **map);
int		largest_line(char **temp);
void	ft_error(t_all *all, char **tab, char *line, char *print);
int		key_release(int c, t_all *all);
int		check_loop(t_all *all);
void	check_donne(t_all *all, int *x, int *y);
int		ok(t_all *all);
void	ft_read_info(t_all *all, int fd);
int		get_next_line(int fd, char **line);
int		check_loop(t_all *all);
int		free_close(t_all *all);
void	free_infos(t_all *all);
char	ft_which_line(char *str);
void	get_map(t_all *all, char **line, int fd);
char	*ft_dup(char **dest, char *src);
void	ft_move(char *str, int *size);
int		ft_compare(char *str, char c);
char	*ft_concate(char *s1, char *s2);
int		ft_length(char *str);
char	**ft_split(char const *s, char c);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_all *all, int *a, int *b);
void	draw_line_wangle(t_all *all, int *a, int *b, float angle);
void	check_points(t_all *all);
void	check_format(t_all *all, int argc, char *argv[]);
int		point_fdf(char *str);
void	adjust_point(t_all *all);
void	print_tab(t_all *all);
void	deplace_center(t_all *all);

#endif
