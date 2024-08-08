/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_mouse_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:48:34 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:47:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_mouse_wheel(int wheel, t_prog *prog)
{
		double x_a = prog->g.x_bound.a;
		double x_b = prog->g.x_bound.b;
		double y_a = prog->g.y_bound.a;
		double y_b = prog->g.y_bound.b;

		double dir_x = (1.0 * prog->mx / prog->w_size);
		double dir_y = (1.0 * prog->my / prog->w_size);
		double p_x = x_a + (x_b - x_a) * dir_x;
		double p_y = y_a + (y_b - y_a) * dir_y;

		float zoom = 1.2;
		
		if (wheel > 0) {
			zoom = 0.9;
		}

		prog->g.zoom += CZOOM * wheel * prog->g.zoom;
		x_a = (x_b + x_a - zoom * (x_b - x_a)) / 2.0;
		x_b = (x_b + x_a + zoom * (x_b - x_a)) / 2.0;
		y_a = (y_b + y_a - zoom * (y_b - y_a)) / 2.0;
		y_b = (y_b + y_a + zoom * (y_b - y_a)) / 2.0;

		prog->g.x_bound.a = p_x - (x_b - x_a) * (dir_x);
		prog->g.x_bound.b = p_x + (x_b - x_a) * (1.0 - dir_x);
		prog->g.y_bound.a = p_y - (y_b - y_a) * (dir_y);
		prog->g.y_bound.b = p_y + (y_b - y_a) * (1.0 - dir_y);

		prog->g.step_x = (prog->g.x_bound.b - prog->g.x_bound.a) / prog->w_size;
		prog->g.step_y = (prog->g.y_bound.b - prog->g.y_bound.a) / prog->w_size;
	
	return (0);
}
