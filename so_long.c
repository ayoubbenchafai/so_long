/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:14 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/25 22:30:27 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

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
void clear_player_image(void *mlx_ptr, void *win_ptr, int x, int y, int width, int height)
{
    void *img;
    char *data;
    int bpp; // bytes per pixel
    int size_line; // size of a line in bytes
    int endian; // endian type

    // Create a new image
    img = mlx_new_image(mlx_ptr, width, height);
    // Get the image data
    data = (char *)mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Clear the image (assuming  32 bits per pixel)
    for (int i =  0; i < height; i++)
    {
        for (int j =  0; j < width; j++)
        {
            // Assuming the background is black (0x00000000)
            *(int *)(data + ((i * width + j) *  4)) =  0x00000000;
        }
    }

    // Draw the cleared image over the player's previous position
    mlx_put_image_to_window(mlx_ptr, win_ptr, img, x, y);

    // Free the image
    mlx_destroy_image(mlx_ptr, img);
}

void update_position(t_mlx_data *data, int direction)
{
    if(direction == 2) // D
    {
        printf("direction : D : %d\n", direction);
        
        data->player.x += 50;
        printf("data->player.x : (x : %d, y : %d)\n", data->player.x, data->player.y);

        
    }
    else  if(direction == 0) // A 
     {
        printf("direction : A : %d\n", direction);

        data->player.x -= 50;
        printf("data->player : (x : %d, y : %d)\n", data->player.x , data->player.y);
     }
    
    else  if(direction == 13) //W
     {
        printf("direction :  W : %d\n", direction);

        data->player.y -= 50;
        printf("data->player : (x : %d, y : %d)\n", data->player.x,data->player.y);
        
     }
    else if(direction == 1) //S
     {
        printf("direction : S : %d\n", direction);
        data->player.y += 50;
        printf("data->player : (x : %d, y : %d)\n", data->player.y, data->player.y);
     }
    mlx_clear_window(data->mlx_ptr, data->win_ptr); //right now return nothing
    // mlx_destroy_image(data->mlx_ptr, data->img);
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
        mlx_destroy_window(data->mlx_ptr, data->mlx_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
    printf("key : %d\n", key);
    return (0);
}
char *get_path_image(int component)
{
    char *path = NULL;;
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
    else
        path = "./images/exitt.xpm";
    return (path);
}


int main()
{
    t_mlx_data data;
    
    data.mlx_ptr = mlx_init();
    // established a connection with a graphical server
    
    //create a window
    data.win_ptr = mlx_new_window(data.mlx_ptr, 650,250, "./so_long");
    int width = 50; // 13
    int height = 50; // 5 

    char *s = "1111111111111\n1C0100C0000C1\n1000011111001\n1P0011E000C01\n1111111111111\n";
    int x = 0,y = 0;
    int x_w ;
    int y_h = 0;
    int i = 0;
    while(y_h <= 650)
    {
        x_w = 0;
        while(x_w <= 250)
        {
            data.img = mlx_xpm_file_to_image(data.mlx_ptr, get_path_image(s[i++]), &width, &height);    
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x + x_w , y + y_h);
                x_w += 50;
        }
        y_h += 50;
    }
data.player.x = 0;
    data.player.y = 0;
    // mlx_loop_hook(mlx, clearPlayer, mlx); // Set the clearPlayer function as the loop hook
    // mlx_loop_hook(data.mlx_ptr, clearPlayer, &data);
    mlx_key_hook(data.win_ptr, key_hook, &data);
    
    // this loop that is keeping the window rendering on the screen
    //keeps the process alive
    mlx_loop(data.mlx_ptr);
    return (0);    
}