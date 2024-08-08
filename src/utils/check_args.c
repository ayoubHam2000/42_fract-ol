/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:18:39 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:53:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	help(void)
{
	ft_put_str("\n");
	ft_put_str("fractol <windows_size> <depth> <fractal_nbr>");
	ft_put_str("[julia_reel_const] [julia_imaginary_const]\n\n");
	ft_put_str("fractal_nbr\n");
	ft_put_str("\t1 : Mandelbrot set\n");
	ft_put_str("\t2 : Julia set\n");
	ft_put_str("\t3 : Nova set\n\n");
	ft_put_str("Default values of julia_reel_const and");
	ft_put_str("julia_imaginary_const is 0\n\n");
	ft_put_str("Info: \n");
	ft_put_str("\t-Arrows keys for moving the view\n");
	ft_put_str("\t-Zoom out and in using the mouse wheel\n");
	ft_put_str("\t-ESC for exit\n\n");
	ft_put_str("Example : ./fractol 2 0 -0.8\n\n");
	exit(0);
}

void	check_args(int ac, char **av)
{
	int	fract;

	if (ac <= 3)
		help();
	if (ft_atoi(av[1]) <= 50 || ft_atoi(av[1]) >= 1500)
		help();
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[2]) >= 1001)
		help();
	fract = ft_atof(av[3]);
	if (fract < 1 || fract > 3)
		help();
}
