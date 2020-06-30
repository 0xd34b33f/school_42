/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <lcassaun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:23:10 by lcassaun          #+#    #+#             */
/*   Updated: 2020/06/30 17:22:15 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

float	**fdf_split(t_mlx *mlx, char **av)
{
	float	**temp;
	char	**nbr;
	char	*line;
	int		y;
	int		x;

	y = 0;
	temp = malloc(sizeof(float *) * mlx->y_max);
	mlx->fd = open(av[1], O_RDONLY);
	while ((get_next_line(mlx->fd, &line) > 0) && (y < mlx->y_max))
	{
		nbr = ft_strsplit(line, ' ');
		free(line);
		x = 0;
		temp[y] = malloc(sizeof(float) * mlx->x_max);
		while (x < mlx->x_max)
		{
			temp[y][x] = (float)ft_atoi(nbr[x]);
			free(nbr[x++]);
		}
		free(nbr);
		y++;
	}
	return (temp);
}

t_mlx	*map_parsing(char **av)
{
	t_mlx	*mlx;

	if (!(mlx = malloc(sizeof(t_mlx))))
	{
		ft_putstr_fd("Mlx malloc ERROR.\n", 2);
		return (NULL);
	}
	mlx->fd = open(av[1], O_RDONLY);
	if (mlx->fd < 0 || read(mlx->fd, 0, 0) < 0)
	{
		ft_putstr_fd("Usage : ./fdf <filename> [ case_size z_size ]\n", 2);
		close(mlx->fd);
		free(mlx);
		return (NULL);
	}
	if (fdf_valid_malloc(mlx) == 0)
	{
		ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
		close(mlx->fd);
		free(mlx);
		return (NULL);
	}
	if (!(mlx->pxl[0][0]))
	{
		ft_putstr_fd("No data found.\n", 2);
		close(mlx->fd);
		free(mlx);
		return (NULL);
	}
	close(mlx->fd);
	mlx->pxl = fdf_split(mlx, av);
	return (mlx);
}