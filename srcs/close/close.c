/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:10:56 by ssar              #+#    #+#             */
/*   Updated: 2021/07/04 13:09:01 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	free_infos(t_all *all)
{
	if (all->alloue[0] == 1)
		ft_free_tab_int(all->map);
	if (all->alloue[1] == 1)
		ft_free_tab_int(all->value);
	mlx_destroy_display(all->vars.mlx);
	free(all->vars.mlx);
}

int	free_close(t_all *all)
{
	mlx_loop_end(all->vars.mlx);
	mlx_destroy_window(all->vars.mlx, all->vars.win);
	mlx_destroy_image(all->vars.mlx, all->img.img);
	return (0);
}

int	key_release(int c, t_all *all)
{
	if (c == 65307)
		free_close(all);
	return (0);
}

int	check_loop(t_all *all)
{
	if (!all->map)
		return (1);
	return (0);
}
