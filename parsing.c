/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/26 17:51:00 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "string.h"

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

int check_char1(char *s, char c)
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
void f(){system("leaks a.out");}

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



int main()
{
    char *s;
    int fd;
    char *tmp; 
    char **map;
    char *filename; 
    
    filename = "./maps/map.ber";//av[1]
    fd = open(filename, O_RDWR);
    if(fd < 0)
        return (1);
    // atexit(f);

    tmp = NULL;
    while(1)
    {
        s = get_next_line(fd);
        if(!s)
        {
            close(fd);
            break;
        }
        tmp = ft_join_free(tmp, s);
        free(s);
    }
    printf("%s", tmp);
    free(tmp);
    
    printf("------------(check_components) (E C P)---------------\n");
    if(check_components(tmp))
        printf("all exists\n");
    else if(!check_components(tmp) || (len_char(tmp, 'P') || len_char(tmp, 'E')))
        write(1,"Error\n",6);
    printf("------------(check duplicates E P) ==> (error)-------------\n");     
    if(len_char(tmp, 'P') || len_char(tmp, 'E'))
        write(1,"Error\n",6);
    printf("------------------------------------------------------\n");

    // =========================================
    map = ft_split(tmp, '\n');
    char **res = map;
    if(!map)
        return (free(tmp), 1);
        
    int i = -1;
    int width = ft_strlen(map[0]);
    while(map[++i])
    {
        if(width != ft_strlen(map[i]))
            return (free_array(map), write(1, "Error\nInvalid map1.\n", 18), 1);
        if(map[i][0] != '1' || map[i][width - 1] != '1')
            return (free_array(map), write(1, "Error\nInvalid map.\n", 18), 1);
    }
    int height = nbr_strings(tmp, '\n');
    if(height == width)
        write(1,"Error\n",6);

    printf("============The map must be closed/surrounded by walls============\n");
    
    if(check_char1(map[0], '1')  || check_char1(map[height - 1], '1'))
        printf("error\n");
    printf("height : %d\n", height);
    printf("width : %d\n", width);
    free_array(res);
    return (0);
}