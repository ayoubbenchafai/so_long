/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/01 12:58:38 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}
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

void flood_fill(t_data *data, int x, int y)
{
    if (data->c_map[y/50][x/50] == '1' || data->c_map[y/50][x/50] == 'r')
        return;
    data->c_map[y/50][x/50] = 'r';
    flood_fill(data, x, y + 50); 
    flood_fill(data, x, y - 50); 
    flood_fill(data, x + 50, y); 
    flood_fill(data, x - 50, y);
}
char  *fill_string(t_data data, char *av)
{
    char *s;
    char *tmp;

    tmp = NULL;
    data.fd = open(av, O_RDWR); // update option O_RDWR
    if(data.fd < 0)
        return (NULL);
    while(1)
    {
        s = get_next_line(data.fd);
        if(!s)
        {
            close(data.fd);
            break;
        }
        if(ft_strlen(s) == 1)
            return (close(data.fd), free(s), write(1,"Error\n",6), NULL);
        tmp = ft_join_free(tmp, s);
        free(s);
    }
    close(data.fd);
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
    if(!s)
        return (0);
    while(s[i])
    {
        if(!ft_check(ptr, s[i]))
            return (0);
        i++;
    }
    return (1);
}

int is_duplicate(char *s, char c)
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

void free_data(t_data data, int vlag)
{
    if(vlag == 1)
        write(1,"Error\nInvaid Map.\n", 18);
    free(data.s);
    free_array(data.map);
    free_array(data.c_map);
}

int  check_errors(t_data data)
{
    int i;
    int width;
    int height;
    
    if(!check_components(data.s) || !another_char(data.s)) // check all components exists
        // return (free(data.s), free_array(data.map), write(1,"Error\n",6), 1);
        return (free_data(data, 1), 1);
    if(len_char(data.s, 'P') || len_char(data.s, 'E') || !data.map)
        // return (free(data.s), free_array(data.map), write(1,"Error\n",6), 1);
        return (free_data(data, 1), 1);
    i = -1;
    width = ft_strlen(data.map[0]);
    height = nbr_strings(data.s, '\n');
    while(data.map[++i])
    {
        if(width != ft_strlen(data.map[i])) //length
            return (free_data(data, 1), 1);
        if(data.map[i][0] != '1' || data.map[i][width - 1] != '1')
            return (free_data(data, 1), 1);
    }
    if(height == width) // rectangulare
        return (free_data(data, 1), 1);
    if(is_duplicate(data.map[0], '1')  || is_duplicate(data.map[height - 1], '1'))
        return (free_data(data, 1), 1);
    return (0);
}



int check_flood_fill(t_data data)
{
    int i;
    int j;
    int x;
    int y;
    
    i = -1;
    while(++i < data.height)
    { 
        j = -1;
        while(++j < data.width)
        {
            if(data.map[i][j] == 'P')
            {
                x = j * 50;
                y = i * 50;
            }
        }
    }
    flood_fill(&data, x, y);
    j = -1;
    while(data.c_map[++j])
    {
        if(ft_check(data.c_map[j], 'C') || ft_check(data.c_map[j], 'E'))
            return (1);
    }
    return (0);
}



char *get_image(int component)
{
    char *path; //check _path
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
            if (map[i][j] == 'C')
                k++;
            j++;    
        }
        i++;
    }
    return (k);
}

void *ft_mlx_xpm_file_to_image(t_data *data, char *filename)
{   
    //check_filename
    data->img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &data->img_w, &data->img_h);
    if(data->img  == NULL)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free_data(*data, 0);
        exit(1);
    }
    return (data->img);
}

void *ft_mlx_new_window(t_data *data)
{
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->width * 50, data->height * 50, "./so_long");
    if(data->win_ptr  == NULL)
    {
        mlx_destroy_image(data->mlx_ptr, data->img);
        free_data(*data, 0);
        exit(1);
    }
    return (data->win_ptr);
}

t_data    mlx(t_data data, int x, int y)
{
    data.mlx_ptr = mlx_init();
    if(data.mlx_ptr == NULL)
    {
        free_data(data, 0);
        exit(1);
    }
    data.win_ptr = ft_mlx_new_window(&data);
    while(++y < data.height)
    {
        x = -1;
        while(++x < data.width)
        {
            if(data.map[y][x] == 'P')
            {
                data.player.x = x * 50;
                data.player.y = y * 50;  
            }
            data.img = ft_mlx_xpm_file_to_image(&data, get_image(data.map[y][x]));
            mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, x * 50, y * 50);
        }
    }
    return (data);
}

void update_position(t_data *data, int new_x, int new_y)
{
    static int  i;
    int         k;
    
    k = get_nbr_collectible(data->map, data->height,data->width);
    data->img = ft_mlx_xpm_file_to_image(data, "../images/texture_black.xpm");
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);
    if(data->map[new_y/50][new_x/50] == 'C')
        data->map[new_y/50][new_x/50] = '0';
    if(k == 0 && data->map[new_y/50][new_x/50] == 'E')
        exit(0);
    if(data->map[new_y/50][new_x/50] != '1'  && data->map[new_y/50][new_x/50] != 'E')
    {
        data->player.x = new_x;  
        data->player.y = new_y;  
        ft_putnbr(++i);
        ft_putchar('\n');
    }
    data->img = ft_mlx_xpm_file_to_image(data, "../images/player.xpm");
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->player.x, data->player.y);  
}
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_image(data->mlx_ptr, data->img);
    free_data(*data, 0);
    exit(0);
    return (0);
}
int key_hook(int key, t_data *data)
{
    int new_x;
    int new_y;
    
    new_y= data -> player.y;
    new_x = data -> player.x;
    if(key == 53)
        exit(0);
    if(key == 2)
        new_x += 50;
    else if(key == 0)
        new_x -= 50;
    else if(key == 13)
        new_y -= 50;
    else if(key == 1)
        new_y += 50; 
    update_position(data, new_x ,new_y);    
    return (0);
}
void f(){system("leaks a.out");}
int main(int ac, char *av[])
{
    t_data data;
    atexit(f);
    data.s = fill_string(data, av[1]);
    if(!av || !data.s || ac != 2)
        return (write(1,"Error\n",6), 1);
    data.map = ft_split(data.s , '\n');
    data.c_map = ft_split(data.s , '\n');
    if(!data.map || !data.c_map)
    if(!data.map)
        return (free(data.s), 1);
    if(check_errors(data))
        return (1);
    data.height = 0;
    while(data.map[data.height])
        (data.height)++;    
    data.width  = ft_strlen(data.map[0]);
    data.img_h = 50;
    data.img_w = 50;
    if(check_flood_fill(data))
        return (write(1,"Error\nflood fill\n",17), 1);
    data = mlx(data, -1, -1);
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}


// void mlx_new_window()
//fllod(fill)
// if(map == 1 || map = r)
    // return ;
//map == r a


  // Clean up
    // mlx_destroy_image(mlx_ptr, img);
    // mlx_destroy_window(mlx_ptr, win_ptr);


//17 0
//free(map)
// destroy_win
// exit(0)