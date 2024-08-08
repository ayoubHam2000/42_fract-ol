/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:41:27 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/09 17:07:17 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	graph_loop(t_prog *prog)
{
	int	color;
	t_double	X;
	t_double	Y;

	for (int x = 0; x < prog->w_size; x++)
	{
		for (int y = 0; y < prog->w_size; y++)
		{
			X = prog->g.step_x * x + prog->g.x_bound.a;
			Y = prog->g.step_y * y + prog->g.y_bound.a;
			color = prog->f(prog, X, Y);
			ft_put_pixel(prog->img, x, y, color);
		}
	}
}
