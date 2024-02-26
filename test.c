/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:05:12 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/26 16:05:30 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_player
{
    int x;
    int y;
}      t_player;

typedef struct s_mlx_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img;
    t_player player;
}               t_mlx_data;

// w : 13
// a : 0
// s : 1
// d : 2

int len_char(char *s, char c)
{
    int i = 0;
    while (*s)
    {
        if(*s == c)
            i++;
        s++;
    }
    if(i > 1)
        return (1);
    return (0);  
}
int check_components(char *s)
{
    char    *ptr;

    ptr = "01CEP";
    while(*ptr)
    {
        if(!ft_check(s, *ptr))
            return (0);
        ptr++;
    }
    return (1);
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

int handle_input(int key, t_mlx_data *data)
{
    if(key == 53)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        // free(data->mlx_ptr);
        return (1);
    }
    printf("the %d key has been pressed!\n", key);
    return (0);
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
    // clearPlayer(data); f
    mlx_clear_window(data->mlx_ptr, data->win_ptr); //right now return nothing

    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);

}

int key_hook(int key, t_mlx_data *data)
{
    if(key == 53) //escap
        exit(0);        
    if(key == 2) // D
        update_position(data, 2);
    else if(key == 0)  // A 
        update_position(data, 0);    
    else if(key == 13) //W
        update_position(data, 13);
    else if(key == 1) //S
        update_position(data, 1);
    return (0);
}
int main()
{
    t_mlx_data  data;
    data.mlx_ptr = mlx_init();
    int img_width = 50;
    int img_height = 50;
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "./so_long");
    char *s = "1111111111111\n1C0100C0000C1\n1000011111001\n1P0011E000C01\n1111111111111\n";


    int x = 0,y = 0;
    int x_w ;
    int y_h = 0;
    int i = 0;
    while(y_h <= HEIGHT)
    {
        x_w = 0;
        while(x_w <= WIDTH)
        {
            data.img = mlx_xpm_file_to_image(data.mlx_ptr, get_path_image(s[i++]), &img_width, &img_height);    
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x + x_w , y + y_h);
                x_w += 50;
        }
        y_h += 50;
    }
    // mlx_key_hook(data.mlx_ptr, handle_input, &data);
    data.player.x = 50;
    data.player.y = 150;
    mlx_key_hook(data.win_ptr, key_hook,  &data);
    mlx_loop(data.mlx_ptr);







    // char *filename = "./maps/map.ber";
    // int fd = open(filename, O_RDWR);
    // if(fd < 0)
    //     return (1);
    
    // char *s = get_next_line(fd);
    // char *tmp = NULL;
    // if(!s)
    //     return (1);
    // int len_s = ft_strlen(s);
    // while(s)
    // {
    //     int k = ft_strlen(s);
    //     if(k != len_s)
    //         return (free(s), write(1, "Error\n", 6), 1);
    //     tmp = ft_join_free(tmp, s);
    //     s = get_next_line(fd);
    // }
    // int j = -1;
    // int height = 0;
    // int width = len_s;
    // while(tmp[++j])
    // {
    //     if(tmp[j] == '\n')
    //         height++;
    // }
    // printf("------------(rectangular)---------------\n");
    // if(height == width)
    //     write(1,"Error\n",6);
    // printf("------------(just prints)---------------\n");

    // printf("%s", tmp);
    // printf("height : %d\n", height);
    // printf("width : %d\n", width);

    // printf("------------(check_components) (E C P)---------------\n");
    // if(check_components(tmp))
    //     printf("all exists\n");
    // else
    //     printf("Error\n");     
        

    // printf("------------(check duplicates E P) ==> (error)-------------\n");     
    // if(len_char(tmp, 'P') || len_char(tmp, 'E'))
    //     write(1,"Error\n",6);    
    return (0);
}