/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:32:06 by ssar              #+#    #+#             */
/*   Updated: 2021/07/06 09:13:39 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	treat_point(t_all *all, int i, int j, int nb)
{
	int		x;
	int		y;
	int		a[2];
	float	div;

	x = all->h_g[0];
	y = all->h_g[1];
	x = x + ((all->case_size * i) * cos(3.66519));
	y = y - ((all->case_size * i) * sin(3.66519));
	x = x + ((all->case_size * j) * cos(5.75995));
	y = y - ((all->case_size * j) * sin(5.75959));
	a[0] = x;
	a[1] = y;
	x = a[0];
	if (ALT_CASE == 0)
	{
		div = all->case_size / all->map_row;
		if (div < 1)
			div = all->case_size - all->add;
	}
	else
		div = all->case_size - all->add;
	y = a[1] - (nb * div);
	all->value[i][j * 2] = x;
	all->value[i][(j * 2) + 1] = y;
}

void	is_overflow(t_all *all, int *hight_y, int *low_y)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	*hight_y = all->value[0][j + 1];
	*low_y = all->value[0][j + 1];
	while (++i < all->map_row)
	{
		j = 0;
		while (j < all->map_col * 2)
		{
			if (all->value[i][j + 1] < *hight_y)
				*hight_y = all->value[i][j + 1];
			if (all->value[i][j + 1] > *low_y)
				*low_y = all->value[i][j + 1];
			j = j + 2;
		}
	}
}

void	adjust_point(t_all *all)
{
	int	hight_y;
	int	low_y;
	int	i;
	int	j;

	is_overflow(all, &hight_y, &low_y);
	all->add = 0;
	while (hight_y < 0 && low_y < all->y_screen)
	{
		all->add++;
		i = -1;
		while (all->map[++i])
		{
			j = -1;
			while (++j < all->map_col)
				treat_point(all, i, j, all->map[i][j]);
		}
		is_overflow(all, &hight_y, &low_y);
	}
	if (CENTER == 1)
		deplace_center(all);
}

void	check_points(t_all *all)
{
	int	i;
	int	j;

	i = -1;
	all->value = (int **)malloc(sizeof(int *) * (all->map_row + 1));
	if (!all->value)
		ft_error(all, NULL, NULL, strerror(errno));
	all->value[all->map_row] = 0;
	all->alloue[1] = 1;
	while (++i < all->map_row)
	{
		all->value[i] = (int *)malloc(sizeof(int) * (all->map_col * 2));
		if (!all->value[i])
			ft_error(all, NULL, NULL, strerror(errno));
	}
	i = -1;
	while (all->map[++i])
	{
		j = -1;
		while (++j < all->map_col)
		{
			all->add = 0;
			treat_point(all, i, j, all->map[i][j]);
		}
	}
}
