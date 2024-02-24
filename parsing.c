/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:07:42 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/24 16:43:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "string.h"

// int parsing(void)
// {
//      char *filename = "./maps/map.ber";
//     int fd = open(filename, O_RDWR);
//     if(fd < 0)
//         return (1);
    
//     char *s = get_next_line(fd);
//     char *tmp = NULL;
//     if(!s)
//         return (1);
//     int len_s = ft_strlen(s);
//     while(s)
//     {
//         int k = ft_strlen(s);
//         if(k != len_s)
//             return (free(s), write(1, "Error\n", 6), 1);
//         tmp = ft_join_free(tmp, s);
//         s = get_next_line(fd);
//     }
//     int j = -1;
//     int height = 0;
//     int width = len_s;
//     while(tmp[++j])
//     {
//         if(tmp[j] == '\n')
//             height++;
//     }
//     printf("------------(rectangular)---------------\n");
//     if(height > width)
//         write(1,"Error\n",6);
//     printf("------------(just prints)---------------\n");

//     printf("%s", tmp);
//     printf("height : %d\n", height);
//     printf("width : %d\n", width);

//     printf("------------(check_components) (E C P)---------------\n");
//     if(check_components(tmp))
//         printf("all exists\n");
//     else
//         printf("Error\n");     
        

//     printf("------------(check duplicates E P) ==> (error)-------------\n");     
//     if(len_char(tmp, 'P') || len_char(tmp, 'E'))
//         write(1,"Error\n",6);
// }

int main()
{
    return (0);
}