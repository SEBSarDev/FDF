/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:12:42 by ssar              #+#    #+#             */
/*   Updated: 2021/07/05 10:08:29 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		bpp;

	bpp = data->bits_per_pixel;
	dest = data->addr + (y * data->line_length + x * (bpp / 8));
	*(unsigned int *)dest = color;
}

void	draw_line_wangle(t_all *all, int *a, int *b, float angle)
{
	int	x;
	int	y;
	int	i;
	int	j;

	j = 0;
	i = 0;
	x = a[0];
	y = a[1];
	b[0] += 0;
	while (x >= 0 && x < all->x_screen
		&& y >= 0 && y < all->y_screen && j <= all->g)
	{
		x = a[0] + (i * cos(angle));
		y = a[1] - (i * sin(angle));
		i++;
		if (x >= 0 && x <= all->x_screen && y >= 0 && y <= all->y_screen)
			my_mlx_pixel_put(&all->img, x, y, 0xFFFFFFFF);
		j++;
	}
}

float	get_angle(int *a, int *b, int *g)
{
	int		l;
	int		hypothenuse;
	float	angle;
	float	size;
	float	hypo;

	l = abs(a[0] - b[0]);
	hypothenuse = (l * l) + (abs(a[1] - b[1]) * abs(a[1] - b[1]));
	hypo = sqrt(hypothenuse);
	*g = (int)hypo;
	size = (float)l / (float)hypo;
	angle = acos(size);
	if (a[0] - b[0] > 0 && a[1] - b[1] >= 0)
	{
		angle = 1.5708 - angle;
		angle = 1.5708 + angle;
	}
	else if (a[0] - b[0] < 0 && a[1] - b[1] < 0)
	{
		angle = 1.5708 - angle;
		angle = 4.71239 + angle;
	}
	else if (a[1] - b[1] < 0)
		angle = 3.14159 + angle;
	return (angle);
}

void	place_print(t_all *all, int i, int j)
{
	int		a[2];
	int		b[2];
	float	angle;

	if (i - 1 >= 0)
	{
		a[0] = all->value[i][j];
		a[1] = all->value[i][j + 1];
		b[0] = all->value[i - 1][j];
		b[1] = all->value[i - 1][j + 1];
		angle = get_angle(a, b, &all->g);
		draw_line_wangle(all, a, b, angle);
	}
	if (j - 1 >= 0)
	{
		a[0] = all->value[i][j];
		a[1] = all->value[i][j + 1];
		b[0] = all->value[i][j - 2];
		b[1] = all->value[i][j - 1];
		angle = get_angle(a, b, &all->g);
		draw_line_wangle(all, a, b, angle);
	}
}

void	print_tab(t_all *all)
{
	int	i;
	int	j;

	i = -1;
	while (all->value[++i])
	{
		j = 0;
		while (j < (all->map_col * 2))
		{
			place_print(all, i, j);
			j += 2;
		}
	}
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
}
