/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:36:02 by ssar              #+#    #+#             */
/*   Updated: 2021/07/04 20:49:10 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	adjust_pos(t_all *all, int x, int y)
{
	int	c;
	int	a[2];

	c = all->case_size;
	all->h_g[0] = x;
	all->h_g[1] = y;
	all->b_g[0] = (all->h_g[0] + ((c * all->map_row) * cos(3.66519)));
	all->b_g[1] = (all->h_g[1] - ((c * all->map_row) * sin(3.66519)));
	a[0] = all->b_g[0];
	a[1] = all->b_g[1];
	all->b_d[0] = (a[0] + ((c * all->map_col) * cos(5.75959)));
	all->b_d[1] = (a[1] - ((c * all->map_col) * sin(5.75959)));
	a[0] = all->h_g[0];
	a[1] = all->h_g[1];
	all->h_d[0] = (a[0] + ((c * all->map_col) * cos(5.75959)));
	all->h_d[1] = (a[1] - ((c * all->map_col) * sin(5.75959)));
}

void	get_case(t_all *all, int len)
{
	if (all->map_col > all->map_row)
	{
		all->case_size = len / all->map_col;
		if (all->case_size < 1)
			all->case_size = 10;
	}
	else
	{
		all->case_size = len / all->map_col;
		if (all->case_size < 15)
			all->case_size = 100;
	}
	adjust_pos(all, all->x_screen / 2, 0);
	while (all->case_size > 0 && (all->b_g[0] < 0
			|| all->h_g[1] < 0
			|| all->h_d[0] > all->x_screen
			|| all->b_d[1] > all->y_screen))
	{
		all->case_size--;
		adjust_pos(all, all->x_screen / 2, 0);
	}
	all->case_size = all->case_size + ZOOM;
	if (all->case_size <= 1)
		all->case_size = 2;
}

void	get_position(t_all *all)
{
	int	x;
	int	y;
	int	i;
	int	hypo;
	int	len;

	i = 0;
	x = 0;
	y = 0;
	while (x >= 0 && x <= all->x_screen && y >= 0 && y <= all->y_screen)
	{
		x = x + (i * cos(5.75959));
		y = y - (i * sin(5.75959));
		i++;
	}
	hypo = (abs(x) * abs(x)) + (abs(y) * abs(y));
	len = sqrt(hypo);
	get_case(all, len);
	while (all->h_g[1] < all->y_screen - all->b_d[1])
		adjust_pos(all, all->x_screen / 2, all->h_g[1] + 1);
	while (all->b_g[0] < all->x_screen - all->h_d[0])
		adjust_pos(all, all->h_g[0] + 1, all->h_g[1]);
	while (all->b_g[0] > all->x_screen - all->h_d[0])
		adjust_pos(all, all->h_g[0] - 1, all->h_g[1]);
}

int	ft_run(t_all *all)
{
	int		x;
	int		y;
	void	*bpp;
	void	*ll;

	bpp = &all->img.bits_per_pixel;
	ll = &all->img.line_length;
	x = all->x_screen;
	y = all->y_screen;
	all->vars.win = mlx_new_window(all->vars.mlx, x, y, "fdf");
	all->img.img = mlx_new_image(all->vars.mlx, x, y);
	all->img.addr = mlx_get_data_addr(all->img.img, bpp, ll, &all->img.endian);
	all->alloue[2] = 1;
	get_position(all);
	check_points(all);
	adjust_point(all);
	print_tab(all);
	mlx_hook(all->vars.win, 33, 1L << 2, free_close, all);
	mlx_hook(all->vars.win, 3, 1L << 1, key_release, all);
	mlx_loop_hook(all->vars.mlx, check_loop, all);
	mlx_loop(all->vars.mlx);
	free_infos(all);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_all	all;
	int		i;

	i = -1;
	while (++i < 3)
		all.alloue[i] = 0;
	all.vars.mlx = mlx_init();
	check_format(&all, argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error(&all, NULL, NULL, strerror(errno));
	ft_read_info(&all, fd);
	close(fd);
	ft_run(&all);
	exit(EXIT_SUCCESS);
}
