/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <lcassaun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:36:37 by lcassaun          #+#    #+#             */
/*   Updated: 2020/06/27 08:34:44 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int 	key_hook(int key, t_mlx *mlx)
{
	printf("%d\n", key);
	if (key == 126)
		mlx->shift_y -= 10;
	if (key == 125)
		mlx->shift_y += 10;
	if (key == 123)
		mlx->shift_x -= 10;
	if (key == 124)
		mlx->shift_x += 10;
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	draw(mlx);
	return (0);
}

int 	free_mlx(t_mlx *mlx)
{
	while ((mlx->y_max)-- != 0)
		free((mlx->pxl)[mlx->y_max]);
	free(mlx->pxl);
	close(mlx->fd);
	free(mlx);
	return (0);
}

int main(int ac, char **argv)
{
	t_mlx	*mlx;
	int 	temp_x;
	int 	temp_y;

	mlx = map_parsing(argv);
	if (mlx == NULL)
	{
		ft_putstr("invalid otstrelen\n");
		return (0);
	}
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "fdf");
	mlx->shift_x = 100;
	mlx->shift_y = 100;
	draw(mlx);
	mlx_key_hook(mlx->win_ptr, key_hook, mlx);
	mlx_loop(mlx->mlx_ptr);
//	printf("x = %d\ny = %d\n", mlx->x_max, mlx->y_max);
//	temp_x = mlx->x_max;
//	temp_y = mlx->y_max;
//	while ((mlx->y_max)-- != 1)
//	{
//		mlx->x_max = temp_x;
//		while ((mlx->x_max-- != 1))
//			printf("%3.0f ", (mlx->pxl)[temp_y - mlx->y_max][temp_x - mlx->x_max]);
//		printf("\n");
//	}
//	mlx->x_max = temp_x;
//	mlx->y_max = temp_y;
//	free_mlx(mlx);
//	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xffffff);
//	mlx_string_put(mlx_ptr, win_ptr, 100, 100, 0xffffff, "lol");
	return (0);
}