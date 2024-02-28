/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/28 22:00:51 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int len_char(char *s, char c)
{
    int i;

    i = 0;
    if (!s)
        return (1);
    while (*s)
    {
        if (*s == c)
            i++;
        s++;
    }
    if (i > 1)
        return (i);
    return (0);
}

char  *fill_string(int fd)
{
    char *s;
    char *tmp;

    tmp = NULL;
    while(1)
    {
        s = get_next_line(fd);
        if(!s)
        {
            close(fd);
            break;
        }
        if(ft_strlen(s) == 1)
            return (close(fd), free(s), write(1,"Error\n",6), NULL);
        tmp = ft_join_free(tmp, s);
        free(s);
    }
    return (tmp);
}

void	free_array(char **av)
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
// "1110000CEPW" another char print errors
int  another_char(char *s)
{
    char *ptr = "01CEP\n";
    int i = 0;
    while(s[i])
    {
        if(!ft_check(ptr, s[i]))
            return (0);
        i++;
    }
    return (1);
}

int check_duplicate1(char *s, char c)
{
    if(!s)
        return (1);
    while (*s)
    {
        if(*s != c)
            return (1);
        s++;
    }
    return (0);  
}

int  check_errors(char *s, char **map)
{
    int i;
    int width;
    int height;
    
    if(!check_components(s) || !another_char(s)) // check all components exists
        return (free(s), free_array(map), write(1,"Error\n",6), 1);
    if(len_char(s, 'P') || len_char(s, 'E'))
        return (free(s), free_array(map), write(1,"Error\n",6), 1);
    i = -1;
    width = ft_strlen(map[0]);
    height = nbr_strings(s, '\n');
    while(map[++i])
    {
        if(width != ft_strlen(map[i])) //length
            return (free(s), free_array(map), write(1, "Error\nInvalid map1.\n", 20), 1);
        if(map[i][0] != '1' || map[i][width - 1] != '1')
            return (free(s), free_array(map), write(1, "Error\nInvalid map.\n", 20), 1);
    }
    if(height == width) // rectangulare
        return (free(s), free_array(map), write(1,"Error\n",6), 1);
    if(check_duplicate1(map[0], '1')  || check_duplicate1(map[height - 1], '1'))
        return (free(s), free_array(map), write(1,"Error\n",6), 1);
    return (0);
}

void f(){system("leaks a.out");}

typedef struct s_player
{
    int x;
    int y;
} t_player;

typedef struct s_data
{
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img;
    int         img_w;
    int         img_h;
    int         width;
    int         height;
    char **map;
    t_player    player;
} t_data;

char *get_path_image(int component)
{
    char *path;
    if(component == '1')
        path = "../images/textures1.xpm";
    else if(component == '0')
        path = "../images/texture_black.xpm";
    else if(component == 'P')
        path = "../images/player.xpm";
    else if(component == 'C')
        path = "../images/zyro-image.xpm";
    else if(component == 'E')
        path = "../images/exitt.xpm";
    return (path);
}
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

t_data    mlx(t_data data)
{
    int x;
    int y;
    
    y = 0;
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * 50 , data.height * 50, "./so_long");
    while(y < data.height)
    {
        x = 0;
        while(x < data.width)
        {
            if(data.map[y][x] == 'P')
            {
                data.player.x = x * 50;
                data.player.y = y * 50;  
                
            }
            data.img = mlx_xpm_file_to_image(data.mlx_ptr, get_path_image(data.map[y][x]), &data.img_w, &data.img_h);
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x * 50, y * 50);
            x++;
        }
        y++;
    }
    return data;
}

void update_position(t_data *data, int new_x, int new_y)
{
    
    int         k;
    static int i = 1;
    k = get_nbr_collectible(data->map, data->height,data->width);
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "../images/texture_black.xpm", &data->img_w, &data->img_h);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
    
    if(data->map[new_y/50][new_x/50] == 'C')
        data->map[new_y/50][new_x/50] = '0';
    if(k == 0 && data->map[new_y/50][new_x/50] == 'E')
        exit(0);
   
    if(data->map[new_y/50][new_x/50] != '1'  && data->map[new_y/50][new_x/50] != 'E')
    {
        data->player.x = new_x;  
        data->player.y = new_y;  
        printf("%d\n", i++);

    }
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, "../images/player.xpm", &data->img_w, &data->img_h);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);  
}

int key_hook(int key, t_data *data)
{
    int new_x;
    int new_y;
    
    new_y= data->player.y;
    new_x = data->player.x;
    if(key == 53)
        exit(0);
    if(key == 2) // D
        new_x += 50;
    else if(key == 0) // A
        new_x -= 50;
    else if(key == 13) // W
        new_y -= 50;
    else if(key == 1) // S
        new_y += 50; 
    update_position(data, new_x ,new_y);    
    return (0);
}

int main(int ac, char *av[])
{
    int fd;
    char *s;
    
    t_data data;
    if(ac != 2)
        return (1);    
    fd = open(av[1], O_RDWR);
    if(fd < 0)
        return (1);
    s = fill_string(fd);
    if(!s)
        return (close(fd), 1);
    data.map = ft_split(s, '\n');
    if(!data.map)
        return (free(s), 1);
    if(check_errors(s, data.map))
        return (free(s), free_array(data.map), 1);
    data.height = 0;
    while(data.map[data.height])
        (data.height)++;    
    data.width  = ft_strlen(data.map[0]);
    printf("h : %d\n", data.height);

    data.img_h = 50;
    data.img_w = 50;
    data = mlx(data);
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_loop(data.mlx_ptr);
    free_array(data.map);
    return (0);
}