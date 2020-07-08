/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_mouse_hook.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <lcassaun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 16:25:47 by lcassaun          #+#    #+#             */
/*   Updated: 2020/07/08 17:41:52 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	fr_key_shift(int key, t_fr *fr)
{
	if (key == KEY_W)
	{
		fr->shift_y = -150 / fr->zoom;
		fr->shift_x = 0;
	}
	if (key == KEY_S)
	{
		fr->shift_y = 150 / fr->zoom;
		fr->shift_x = 0;
	}
	if (key == KEY_A)
	{
		fr->shift_x = -150 / fr->zoom;
		fr->shift_y = 0;
	}
	if (key == KEY_D)
	{
		fr->shift_x = 150 / fr->zoom;
		fr->shift_y = 0;
	}
	fr->x1 += (fr->shift_x );
	fr->y1 += (fr->shift_y );
}

int		fr_julia_mouse(int x, int y, t_fr **fr)
{
	if (fr[0]->fr_switch == 1 || fr[0]->fr_switch == 3)
	{
		if (fr[0]->julia == 1)
		{
			if (x < WIDTH && y < HEIGHT)
			{
				if (x < WIDTH / 2 && y < WIDTH / 2)
				{
					fr[0]->c_r += 0.005;
					fr[1]->c_r += 0.005;
					fr[2]->c_r += 0.005;
					fr[3]->c_r += 0.005;
				}
				if (x > WIDTH / 2 && y < WIDTH / 2)
				{
					fr[0]->c_r -= 0.005;
					fr[1]->c_r -= 0.005;
					fr[2]->c_r -= 0.005;
					fr[3]->c_r -= 0.005;
				}
				if (x < WIDTH / 2 && y > WIDTH / 2)
				{
					fr[0]->c_i += 0.005;
					fr[1]->c_i += 0.005;
					fr[2]->c_i += 0.005;
					fr[3]->c_i += 0.005;
				}
				if (x > WIDTH / 2 && y > WIDTH / 2)
				{
					fr[0]->c_i -= 0.005;
					fr[1]->c_i -= 0.005;
					fr[2]->c_i -= 0.005;
					fr[3]->c_i -= 0.005;
				}
			}
			fr_draw(fr);
		}
	}
	return (0);
}

int		fr_mouse(int code, int x, int y, t_fr **fr)
{
	if (code == 4 || code == 1)
	{
		fr_zoom(fr[0], x, y);
		fr_zoom(fr[1], x, y);
		fr_zoom(fr[2], x, y);
		fr_zoom(fr[3], x, y);
		fr_draw(fr);
	}
	else if (code == 5 || code == 2)
	{
		fr_dezoom(fr[0], x, y);
		fr_dezoom(fr[1], x, y);
		fr_dezoom(fr[2], x, y);
		fr_dezoom(fr[3], x, y);
		fr_draw(fr);
	}
	return (0);
}

static void	fr_hidemenu(int key, t_fr **fr)
{
	if (key == KEY_F)
	{
		if (fr[0]->menu == 340)
		{
			fr[0]->menu = 0;
			fr[1]->menu = 0;
			fr[2]->menu = 0;
			fr[3]->menu = 0;
		}
		else
		{
			fr[0]->menu = 340;
			fr[1]->menu = 340;
			fr[2]->menu = 340;
			fr[3]->menu = 340;
		}
		mlx_destroy_image(fr[0]->mlx, fr[0]->img);
		mlx_clear_window(fr[0]->mlx, fr[0]->win);
		fr_draw_menu(fr);
		fr[0]->img = mlx_new_image(fr[0]->mlx, WIDTH - fr[0]->menu, HEIGHT);
		fr[0]->img_str = mlx_get_data_addr(fr[0]->img, &fr[0]->bpp, &fr[0]->strlen, &fr[0]->endian);
		fr[1]->img_str = fr[0]->img_str;
		fr[2]->img_str = fr[0]->img_str;
		fr[3]->img_str = fr[0]->img_str;
		fr[1]->img = fr[0]->img;
		fr[2]->img = fr[0]->img;
		fr[3]->img = fr[0]->img;
		fr_draw(fr);
	}
}

void	fr_key_switch(int key, t_fr **fr)
{
	if (key == KEY_1)
	{
		fr_julia(fr);
	}
	if (key == KEY_2)
	{
		fr_ship(fr);
	}
	if (key == KEY_3)
	{
		fr_chameleon(fr);
	}
	if (key == KEY_4)
	{
		fr_mandelbrot(fr);
	}
}

int		fr_key(int key, t_fr **fr)
{
	fr_key_switch(key, fr);
	if (key == KEY_Q)
	{
		fr[0]->color_index = (fr[0]->color_index + 1) % 5;
		fr[1]->color_index = (fr[1]->color_index + 1) % 5;
		fr[2]->color_index = (fr[2]->color_index + 1) % 5;
		fr[3]->color_index = (fr[3]->color_index + 1) % 5;
		fr_draw(fr);
	}
	if (key == KEY_ESC)
	{
		free(fr[0]);
		free(fr[1]);
		free(fr[2]);
		free(fr[3]);
		free(fr);
		exit(EXIT_SUCCESS);
	}
	if ((key >= 0 && key <= 2) || key == 13)
	{
		fr_key_shift(key, fr[0]);
		fr_key_shift(key, fr[1]);
		fr_key_shift(key, fr[2]);
		fr_key_shift(key, fr[3]);
		fr_draw(fr);
	}
	if (key == KEY_E)
	{
		if (fr[0]->julia == 1)
		{
			fr[0]->julia = 0;
			fr[1]->julia = 0;
			fr[2]->julia = 0;
			fr[3]->julia = 0;
		}
		else
		{
			fr[0]->julia = 1;
			fr[1]->julia = 1;
			fr[2]->julia = 1;
			fr[3]->julia = 1;
		}
	}
	fr_hidemenu(key, fr);
	return (0);
}
