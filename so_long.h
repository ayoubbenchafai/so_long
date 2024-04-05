/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:20:43 by aben-cha          #+#    #+#             */
/*   Updated: 2024/03/02 16:55:20 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_player
{
	int	x;
	int	y;
}			t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	int			img_wh;
	int			width;
	int			height;
	char		**map;
	char		**c_map;
	int			fd;
	char		*s;
	t_player	p;
}			t_data;

int		ft_check(char *s, char c);
char	*get_next_line(int fd);
char	*ft_join_free(char *s, const char *buf);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int		nbr_strings(const char *s, char c);
char	**ft_split(char const *s, char c);
void	ft_putchar(char c);
void	ft_putnbr(int n);
int		len_char(char *s, char c);
int		count_ccurrence(char **map, int h, int w, int c);
char	*fill_string(char *av, int fd);
void	free_array(char **av);
int		check_components(char *s);
int		another_char(char *s);
int		is_dup(char *s, char c);
int		check_errors(t_data data);
void	free_data(t_data data, int vlag);
char	*get_image(int component);
void	*ft_mlx_xpm_file_to_image(t_data *data, char *filename);
void	*ft_mlx_new_window(t_data *data);
int		close_window(t_data *data);
void	ft_putstr(char *s);
t_data	mlx(t_data data, int x, int y);
void	update_position(t_data *d, int new_x, int new_y);
int		key_hook(int key, t_data *data);
void	flood_fill(t_data *data, int x, int y);

#endif
