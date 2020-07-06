/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <lcassaun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 18:24:09 by lcassaun          #+#    #+#             */
/*   Updated: 2020/07/06 19:28:58 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int 	fr_error(char *str, int i_switch)
{
	ft_putstr_fd(str, 2);
	if (i_switch == 1)
		ft_putstr_fd("Valid number of arguments : 1\n", 2);
	if (i_switch == 2)
		ft_putstr_fd("Valid argument : Julia\n", 2);
	return (0);
}

static int 	fr_valid_argv(t_fr **fr)
{
	if (ft_strcmp(fr[0]->argv, "Julia") == 0)
		fr_julia(*fr);
	else if (ft_strcmp(fr[0]->argv, "Mandelbrot") == 0)
		fr_mandelbrot(fr);
	else
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_fr					**fr;
	pthread_t 				*thread_id;

	thread_id = (pthread_t *)malloc(3 * sizeof(pthread_t));
	if (argc != 2)
	{
		return (fr_error("Invalid number of arguments\n", 1));
	}
	fr = (t_fr **)malloc(sizeof(t_fr *) * 1);
	*fr = (t_fr *)malloc(sizeof(t_fr) * 3);
	fr[0]->argv = argv[1];
	printf("1111\n");
	fr[0]->thread_id = thread_id;
	if (fr_valid_argv(fr) == 0)
		return (fr_error("Invalid argument\n", 2));
	return (0);
}
