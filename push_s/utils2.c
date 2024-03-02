/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:18:28 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 16:36:46 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s != '\0')
		write(1, s++, 1);
}

t_data	mlx(t_data data, int x, int y)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		free_data(data, 0);
		exit(1);
	}
	data.win_ptr = ft_mlx_new_window(&data);
	while (++y < data.height)
	{
		x = -1;
		while (++x < data.width)
		{
			if (data.map[y][x] == 'P')
			{
				data.p.x = x * 50;
				data.p.y = y * 50;
			}
			data.img = ft_mlx_xpm_file_to_image(&data,
					get_image(data.map[y][x]));
			mlx_put_image_to_window(data.mlx_ptr,
				data.win_ptr, data.img, x * 50, y * 50);
		}
	}
	return (data);
}

void	update_position(t_data *d, int new_x, int new_y)
{
	int			k;
	static int	i;

	k = count_ccurrence(d -> map, d -> height, d -> width, 'C');
	d -> img = ft_mlx_xpm_file_to_image(d, "./images/route.xpm");
	mlx_put_image_to_window(d -> mlx_ptr, d -> win_ptr,
		d -> img, d -> p.x, d -> p.y);
	if (d -> map[new_y / 50][new_x / 50] == 'C')
		d -> map[new_y / 50][new_x / 50] = '0';
	if (k == 0 && d->map[new_y / 50][new_x / 50] == 'E')
		close_window(d);
	if (d -> map[new_y / 50][new_x / 50] != '1' &&
			d -> map[new_y / 50][new_x / 50] != 'E')
	{
		d -> p.x = new_x;
		d -> p.y = new_y;
		ft_putnbr(++i);
		ft_putchar('\n');
	}
	d -> img = ft_mlx_xpm_file_to_image(d, "./images/player.xpm");
	mlx_put_image_to_window(d -> mlx_ptr, d -> win_ptr,
		d -> img, d -> p.x, d -> p.y);
}

int	key_hook(int key, t_data *data)
{
	int	new_x;
	int	new_y;

	new_y = data -> p.y;
	new_x = data -> p.x;
	if (key == 53)
		close_window(data);
	else if (key == 2)
		new_x += 50;
	else if (key == 0)
		new_x -= 50;
	else if (key == 13)
		new_y -= 50;
	else if (key == 1)
		new_y += 50;
	else
		return (0);
	update_position(data, new_x, new_y);
	return (0);
}

void	flood_fill(t_data *data, int x, int y)
{
	if (data -> c_map[y / 50][x / 50] == '1'
		|| data->c_map[y / 50][x / 50] == 'r')
		return ;
	data -> c_map[y / 50][x / 50] = 'r';
	flood_fill(data, x, y + 50);
	flood_fill(data, x, y - 50);
	flood_fill(data, x + 50, y);
	flood_fill(data, x - 50, y);
}
