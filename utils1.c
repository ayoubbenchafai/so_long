/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:16:36 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 17:43:34 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_data(t_data data, int vlag)
{
	if (vlag == 1)
		ft_putstr("Error\nInvaid Map.\n");
	free(data.s);
	free_array(data.map);
	free_array(data.c_map);
}

char	*get_image(int component)
{
	char	*path;

	path = NULL;
	if (component == '1')
		path = "./images/wall.xpm";
	else if (component == '0')
		path = "./images/route.xpm";
	else if (component == 'P')
		path = "./images/player.xpm";
	else if (component == 'C')
		path = "./images/coins.xpm";
	else if (component == 'E')
		path = "./images/exit.xpm";
	return (path);
}

void	*ft_mlx_xpm_file_to_image(t_data *data, char *filename)
{
	data -> img = mlx_xpm_file_to_image(data -> mlx_ptr,
			filename, &data -> img_wh, &data -> img_wh);
	if (data -> img == NULL)
	{
		ft_putstr("Error\nMalloc.\n");
		mlx_destroy_window(data -> mlx_ptr, data -> win_ptr);
		free_data(*data, 0);
		exit(1);
	}
	return (data -> img);
}

void	*ft_mlx_new_window(t_data *data)
{
	data -> win_ptr = mlx_new_window(data -> mlx_ptr, data->width * 50,
			data -> height * 50, "./so_long");
	if (data -> win_ptr == NULL)
	{
		ft_putstr("Error\nMalloc.\n");
		mlx_destroy_image(data->mlx_ptr, data->img);
		free_data(*data, 0);
		exit(1);
	}
	return (data->win_ptr);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data -> mlx_ptr, data -> win_ptr);
	mlx_destroy_image(data -> mlx_ptr, data -> img);
	free_data(*data, 0);
	exit(0);
	return (0);
}
