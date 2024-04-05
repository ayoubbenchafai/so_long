/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:12:31 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 13:10:51 by aben-cha         ###   ########.fr       */
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

int	len_char(char *s, char c)
{
	int	i;

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

int	count_ccurrence(char **map, int h, int w, int c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (!map)
		return (0);
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j] == c)
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

char	*fill_string(char *av, int fd)
{
	char	*s;
	char	*tmp;

	tmp = NULL;
	fd = open(av, O_RDWR);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
		{
			close(fd);
			break ;
		}
		if (ft_strlen(s) == 1)
			return (close(fd), free(s),
				ft_putstr("Error\nInvalid Map.\n"), exit(1), NULL);
		tmp = ft_join_free(tmp, s);
		free(s);
	}
	close(fd);
	return (tmp);
}
