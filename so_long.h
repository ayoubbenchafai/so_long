/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:43 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/24 22:34:55 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#  define SO_LONG_H

# include <stdlib.h>
#include  <fcntl.h>
#include  <mlx.h>
// #include  <keysym.h>
# include <unistd.h>
# include <stdio.h> //delete it

# define WIDTH 650
# define HEIGHT 250

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct	s_data {
	void	*img;
    // char    *reative_path;
    int img_width;
    int img_height;
	// char	*addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
}				t_data;

int	    ft_check(char *s, char c);
char	*get_next_line(int fd);
char	*ft_join_free(char *s, const char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
#endif