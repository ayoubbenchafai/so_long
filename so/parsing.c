/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/28 12:46:56 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int len_char(char *s, char c)
{
    int i = 0;
    if(!s)
        return (1);
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

int main(int ac, char *av[])
{
    int fd;
    char *s;
    char **map;

    if(ac != 2)
        return (1);    
    fd = open(av[1], O_RDWR);
    if(fd < 0)
        return (1);
    s = fill_string(fd);
    if(!s)
        return (close(fd), 1);
    map = ft_split(s, '\n');
    if(!map)
        return (free(s), 1);
    if(check_errors(s, map))
        return (1);
    int i = 0;
    while(map[i])
    {
        printf("%s\n",map[i]);    
        i++;
    }
    
    return (0);
}