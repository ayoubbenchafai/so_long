/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:14 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/28 13:28:29 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"
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
    char **map;
    t_player player;
}               t_mlx_data;

int is_collision(t_mlx_data *data, int new_x, int new_y) 
{
    if (data->map[new_y / 50][new_x / 50] == '1')
        return  1;
    return  0;
}

void    clearPlayer(t_mlx_data *data)
{
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    return ;   
}

// void update_position(t_mlx_data *data, int direction)
// {
//     int img_height = 50;
//     int img_width = 50;
//     data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/texture_black.xpm", &img_width, &img_height);
//     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
    
//     int new_x = data->player.x;
//     int new_y = data->player.y;
//     // Determine new position based on direction
//     if(direction ==  2) // D
//         new_x +=  50;
//     else if(direction ==  0) // A  
//         new_x -=  50;
//     else if(direction ==  13) // W
//         new_y -=  50;
//     else if(direction ==  1) // S
//         new_y +=  50;

//     // Check for collision with walls
//     if (!is_collision(data, new_x, new_y)) {
//         // If there is no collision, update player position
//         data->player.x = new_x;
//         data->player.y = new_y;
//     }

//     // Redraw the player at the updated position
//     data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/player.xpm", &img_width, &img_height);
//     mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
// }


int get_nbr_collectible(char **map, int h, int w)
{
    int i = 0, j, k = 0;
    if(!map)
        return (-1);
    while(i < h)
    { 
        j = 0;
        while(j < w)
        {
            if(map[i][j] == 'C')
                k++;
            j++;    
        }
        i++;
    }
    return (k);
}
void update_position(t_mlx_data *data, int new_x, int new_y)
{
    char *map[5] = {"1111111111111", 
                    "1C0100C0000C1", 
                    "1000011111001", 
                    "1P0011E000C01", 
                    "1111111111111"};
    
    int img_height = 50;
    int img_width = 50;
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/texture_black.xpm", &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
    if (new_x >= 0 && new_x < 650 && new_y >= 0 && new_y < 250 && map[new_y/50][new_x/50] != '1')
    {
        data->player.x = new_x;
        data->player.y = new_y;
    }
    int j = 0;
    int k = get_nbr_collectible(map, 5,13);
    static int c = 0;
    if (map[new_y/50][new_x/50] == 'C')
       c++;
    printf("c = %d, k = %d\n", c, k);
    if(c == k && map[new_y/50][new_x/50] == 'E')
        exit(0);   
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./images/player.xpm", &img_width, &img_height);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
}

int ft_exit(t_mlx_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_image(data->mlx_ptr, data->img);
    exit(0);
}

int key_hook(int key, t_mlx_data *data)
{
    int new_x = data->player.x;
    int new_y = data->player.y;
    if(key == 53)
        exit(0);
    if (key == 13) // W 
        new_y -=50 ;
    else if (key == 1) // S 
        new_y += 50;
    else if (key == 0) // A 
        new_x-= 50;
    else if (key == 2) // D 
        new_x +=50;
    
    update_position(data, new_x, new_y);
    return (0);
}

void	 free_array(char **av)
{
	int	i;

	i = 0;
	if (!av)
		return ;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
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

int main()
{
    t_mlx_data data;
    
    // established a connection with a graphical server
    data.mlx_ptr = mlx_init();
    
    char *s = "1111111111111\n1C0100C0000C1\n1000011111001\n1P0011E000C01\n1111111111111\n";
    data.map = ft_split(s, '\n');
    if(!data.map)
        return (1);
    
    int k = 0;
    while(data.map[k])
    {
        printf("%s\n", data.map[k]);
        k++;
    }

    int img_height = 50;
    int img_width = 50;
    int height = k;
    int width = ft_strlen(data.map[0]);
    printf("height : %d\n", height);
    printf("width : %d\n", width);

    data.win_ptr = mlx_new_window(data.mlx_ptr, width * 50 , height * 50, "./so_long");

    int x ,y = -1;
    int x_w = 0,y_h = 0;
    int i= 0;
    while(++y < height)
    {
        x = -1;
        while(++x < width)
        {
            if(data.map[y][x] == 'P')
            {
                data.player.x = x * 50;
                data.player.y = y * 50;  
            }
            data.img = mlx_xpm_file_to_image(data.mlx_ptr, get_path_image(data.map[y][x]), &img_width, &img_height);    
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x * 50, y * 50);
            // x++;
        }
        // y++;
    }
     

    mlx_hook(data.win_ptr, 2, 0, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, ft_exit, &data);
    free_array(data.map);

    // this loop that is keeping the window rendering on the screen
    //keeps the process alive
    mlx_loop(data.mlx_ptr);
    return (0);    
}