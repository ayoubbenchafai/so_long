/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:14:45 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 13:15:46 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	check_components(char *s)
{
	char	*ptr;

	ptr = "01CEP";
	while (*ptr)
	{
		if (!ft_check(s, *ptr))
			return (0);
		ptr++;
	}
	return (1);
}

int	another_char(char *s)
{
	int		i;
	char	*ptr;

	ptr = "01CEP\n";
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_check(ptr, s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_dup(char *s, char c)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != c)
			return (1);
		s++;
	}
	return (0);
}

int	check_errors(t_data d)
{
	int		i;
	size_t	w;
	size_t	h;

	if (!check_components(d.s) || !another_char(d.s))
		return (free_data(d, 1), 1);
	if (len_char(d.s, 'P') || len_char(d.s, 'E'))
		return (free_data(d, 1), 1);
	i = -1;
	if (!d.map)
		return (free(d.s), ft_putstr("Error\n"), exit(1), 1);
	w = ft_strlen(d.map[0]);
	h = nbr_strings(d.s, '\n');
	while (d.map[++i])
	{
		if (w != ft_strlen(d.map[i]) || d.map[i][0] != '1'
			|| d.map[i][w - 1] != '1')
			return (free_data(d, 1), 1);
	}
	if (h == w || is_dup(d.map[0], '1') || is_dup(d.map[h - 1], '1'))
		return (free_data(d, 1), 1);
	return (0);
}
