/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 16:53:17 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_flood_fill(t_data d)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (++i < d.height)
	{
		j = -1;
		while (++j < d.width)
		{
			if (d.map[i][j] == 'P')
			{
				x = j * 50;
				y = i * 50;
			}
		}
	}
	flood_fill (&d, x, y);
	if (count_ccurrence(d.c_map, d.height, d.width, 'C')
		|| count_ccurrence(d.c_map, d.height, d.width, 'E'))
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	data.s = fill_string(av[1], data.fd);
	if (!av || !data.s || ac != 2)
		return (ft_putstr("Error\n"), 1);
	data.map = ft_split(data.s, '\n');
	data.c_map = ft_split(data.s, '\n');
	if (!data.map || !data.c_map)
		return (free(data.s), ft_putstr("Error\n"), 1);
	if (check_errors(data))
		return (1);
	data.height = 0;
	while (data.map[data.height])
		(data.height)++;
	data.width = ft_strlen(data.map[0]);
	data.img_wh = 50;
	if (check_flood_fill(data))
		return (free_data(data, 1), 1);
	data = mlx(data, -1, -1);
	mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
