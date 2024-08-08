/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_key_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:35:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:47:07 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_key_up(int keycode, t_prog *prog)
{
	t_double dir_x = 0;
	t_double dir_y = 0;

	if (keycode == KEY_L)
		dir_x = -1 * TRAN;
	else if (keycode == KEY_R)
		dir_x = 1 * TRAN;

	if (keycode == KEY_U)
		dir_y = -1 * TRAN;
	else if (keycode == KEY_D)
		dir_y = +1 * TRAN;

	if (keycode == KEY_A)
		prog->range_shift_color *= cos(prog->range_shift_color * 0.1);
	else if (keycode == KEY_ESC)
		return prog->quit = 1;


	double x_a = prog->g.x_bound.a;
	double x_b = prog->g.x_bound.b;
	double y_a = prog->g.y_bound.a;
	double y_b = prog->g.y_bound.b;

	//translate
	prog->g.x_bound.a += (x_b - x_a) * dir_x;
	prog->g.x_bound.b += (x_b - x_a) * dir_x;
	prog->g.y_bound.a += (y_b - y_a) * dir_y;
	prog->g.y_bound.b += (y_b - y_a) * dir_y;

	//update step
	prog->g.step_x = (prog->g.x_bound.b - prog->g.x_bound.a) / prog->w_size;
	prog->g.step_y = (prog->g.y_bound.b - prog->g.y_bound.a) / prog->w_size;


	return (0);
}
