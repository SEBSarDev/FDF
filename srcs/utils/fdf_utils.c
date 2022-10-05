/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:01:45 by ssar              #+#    #+#             */
/*   Updated: 2021/07/04 21:18:43 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	check_format(t_all *all, int argc, char *argv[])
{
	if (argc != 2)
		ft_error(all, NULL, NULL, "Wrong number of arguments");
	if (argc == 2 && point_fdf(argv[1]) != 1)
		ft_error(all, NULL, NULL, "First argument not a .fdf");
}

int	point_fdf(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'f')
		return (0);
	if (str[i - 2] != 'd')
		return (0);
	if (str[i - 3] != 'f')
		return (0);
	if (str[i - 4] != '.')
		return (0);
	return (1);
}

void	deplace_center(t_all *all)
{
	int	deplace;
	int	i;
	int	j;
	int	y;
	int	x;

	i = -1;
	y = all->map_row / 2;
	x = (all->map_col / 2) * 2 + 1;
	deplace = all->value[y][x] - all->y_screen / 2;
	while (++i < all->map_row)
	{
		j = 0;
		while (j < all->map_col * 2)
		{
			all->value[i][(j) + 1] = all->value[i][(j) + 1] - deplace;
			j = j + 2;
		}
	}
}
