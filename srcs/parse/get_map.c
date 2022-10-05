/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:35:38 by ssar              #+#    #+#             */
/*   Updated: 2021/07/05 09:03:46 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	ft_len_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int	**ft_copy_tabint(t_all *all, int **temp, int i, int k)
{
	int		**str;
	int		j;

	str = (int **)malloc(sizeof(int *) * (i + 1));
	if (!str)
	{
		ft_free_tab_int(temp);
		ft_error(all, NULL, NULL, strerror(errno));
	}
	i = -1;
	while (temp[++i])
	{
		j = -1;
		str[i] = (int *)malloc(sizeof(int) * (k));
		if (!str[i])
		{
			ft_free_tab_int(temp);
			ft_error(all, NULL, NULL, strerror(errno));
		}
		while (++j < k)
			str[i][j] = temp[i][j];
	}
	str[i] = 0;
	ft_free_tab_int(temp);
	return (str);
}

int	**get_int_map(t_all *all, char *line, int **temp, int len)
{
	int		**new_temp;
	int		k;
	int		i;
	int		j;
	char	**split;

	j = -1;
	i = 0;
	split = ft_split(line, ' ');
	k = ft_len_tab(split);
	all->map_col = k;
	new_temp = ft_copy_tabint(all, temp, len, k);
	while (new_temp[i])
		i++;
	new_temp[i] = (int *)malloc(sizeof(int) * (k));
	if (!new_temp[i])
	{
		ft_free_tab_int(new_temp);
		ft_error(all, NULL, NULL, strerror(errno));
	}
	while (split[++j])
		new_temp[i][j] = ft_atoi(split[j]);
	new_temp[i + 1] = 0;
	ft_free_tab(split);
	return (new_temp);
}

void	get_map(t_all *all, char **line, int fd)
{
	int		i;
	int		**temp;

	i = 1;
	temp = (int **)malloc(sizeof(int *));
	if (!temp)
		ft_error(all, line, NULL, strerror(errno));
	temp[0] = 0;
	all->alloue[0] = 1;
	temp = get_int_map(all, *line, temp, i);
	free(*line);
	while (get_next_line(fd, line) > 0)
	{
		temp = get_int_map(all, *line, temp, ++i);
		free(*line);
	}
	all->map = ft_copy_tabint(all, temp, i, all->map_col);
}

void	ft_read_info(t_all *all, int fd)
{
	char	*line;
	int		a;
	int		i;

	a = 1;
	while (a > 0)
	{
		a = get_next_line(fd, &line);
		if (a > 0 && line != NULL)
			get_map(all, &line, fd);
		if (line != NULL)
			free(line);
	}
	if (all->alloue[0] == 0)
		ft_error(all, NULL, NULL, "Empty file is not valid");
	if (a == -1)
		ft_error(all, NULL, line, strerror(errno));
	i = 0;
	while (all->map[i])
		i++;
	all->map_row = i;
	all->x_screen = 1200;
	all->y_screen = 850;
}
