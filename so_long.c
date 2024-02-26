/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:14 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/26 22:38:45 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
// w : 13
// a : 0
// s : 1
// d : 2
typedef struct s_player
{
    int x;
    int y;
}               t_player;

typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *img;
    t_player player;
}               t_mlx_data;

void clearPlayer(t_mlx_data *data)
{
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    return ;   
}

void update_position(t_mlx_data *data, int direction)
{
    int img_height = 50;
    int img_width = 50;
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/texture_black.xpm", &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
    
    if(direction == 2) // D
        data->player.x += 50;
    else  if(direction == 0) // A 
        data->player.x -= 50;
        
    else  if(direction == 13) //W
        data->player.y -= 50;

    else if(direction == 1) //S
        data->player.y += 50;
    printf("%d\n", data->player.x);
    printf("%d\n", data->player.y);
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/player.xpm", &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
}

int key_hook(int key, t_mlx_data *data)
{
    if(key == 53)  //escap
        exit(0);        
    if(key == 2)  //D
        update_position(data, 2);
    else if(key == 0)  //A 
        update_position(data, 0);    
    else if(key == 13) //W
        update_position(data, 13);
    else if(key == 1) //S
        update_position(data, 1);
    return (0);
}

int handel_input(int key, t_mlx_data *data)
{
    if(key == 53)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
    printf("key : %d\n", key);
    return (0);
}
char *get_path_image(int component)
{
    char *path;
    if(component == '1')
        path = "./images/textures1.xpm";
    else if(component == '0')
        path = "./images/texture_black.xpm";
    else if(component == 'P')
        path = "./images/player.xpm";
    else if(component == 'C')
        path = "./images/zyro-image.xpm";
    else if(component == 'E')
        path = "./images/exitt.xpm";
    return (path);
}

int	nbr_strings(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			len++;
		while (*s && *s != c)
			s++;
	}
	return (len);
}

int main()
{
    t_mlx_data data;
    
    data.mlx_ptr = mlx_init();
    // established a connection with a graphical server
    
    //create a window

    char *s = "1111111111111\n1C0100C0000C1\n1000011111001\n1P0011E000C01\n1111111111111\n";
    char *map[5] = {"1111111111111", 
                    "1C0100C0000C1", 
                    "1000011111001", 
                    "1P0011E000C01", 
                    "1111111111111"};
    
    int img_height = 50;
    int img_width = 50;
    int height = nbr_strings(s, '\n');
    int width = ft_strlen(map[0]);
    printf("height : %d\n", height);
    printf("width : %d\n", width);

    data.win_ptr = mlx_new_window(data.mlx_ptr, width * 50 , height * 50, "./so_long");

    int x = 0,y = 0;
    int x_w = 0,y_h = 0;
    int i= 0;
    while(y < height)
    {
        x = 0;
        while(x < width)
        {
            if(map[y][x] == 'p')
            {
                printf("x : %d\n", x);
                printf("y : %d\n", y);
            }
            data.img = mlx_xpm_file_to_image(data.mlx_ptr, get_path_image(map[y][x]), &img_width, &img_height);    
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x * 50, y * 50);
            x++;
        }
        y++;
    }
    data.player.x = 50;
    data.player.y = 150;
    data.img = "./images/player.xpm";
    mlx_key_hook(data.win_ptr, key_hook, &data);
    // this loop that is keeping the window rendering on the screen
    //keeps the process alive
    mlx_loop(data.mlx_ptr);
    return (0);    
}