/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:43 by aben-cha          #+#    #+#             */
/*   Updated: 2024/02/27 21:32:57 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#  define SO_LONG_H

# include <stdlib.h>
#include  <fcntl.h>
#include  <mlx.h>
# include <unistd.h>
# include <stdio.h> //delete it

# define WIDTH 650
# define HEIGHT 250

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int	    ft_check(char *s, char c);
char	*get_next_line(int fd);
char	*ft_join_free(char *s, const char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int	nbr_strings(const char *s, char c);
char	**ft_split(char const *s, char c);

#endif