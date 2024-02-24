/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:14 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/24 22:54:18 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
}               t_mlx_data;
int deal_key(int key, t_mlx_data *data)
{
    if(key == 53)
    {
        mlx_destroy_window(data->mlx_ptr, data->mlx_ptr);
        // free(data->mlx_ptr);
        return(1);
    }
    printf("key : %d\n", key);
    return (0);
}
int main()
{
    // is starting the connection with the graphical server 
    // so it'sstrting the machine if you want 
    // give me back a pointer to the connection
    t_mlx_data    data;
    // established a connection with a graphical server
    data.mlx_ptr =  mlx_init(); 

    //create a window
    
    data.mlx_ptr = mlx_new_window(data.mlx_ptr, 800, 500, "./so_long");
    mlx_key_hook(data.mlx_ptr, deal_key, &data);
    // this loop that is keeping the window rendering on the screen
    //keeps the process alive
    mlx_loop(data.mlx_ptr);
    return (0);    
}