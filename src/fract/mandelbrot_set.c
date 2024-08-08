/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:51:56 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:43:05 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	trans_iter(t_complex z, int *iter)
{
	t_double	log_zn;
	t_double	nu;

	log_zn = log(z.a * z.a + z.b * z.b) / 2;
	nu = log(log_zn / log(2)) / log(2);
	*iter = *iter + 1 - nu;
}

int	mandelbrot_set(t_prog *prog, t_double x, t_double y)
{
	t_complex		z;
	int				iter;
	t_double		xtemp;
	t_complex  p;

	p.a = x;
	p.b = y;
	z.a = 0;
	z.b = 0;
	iter = 0;
	while (z.a * z.a + z.b * z.b <= (1 << 16) && iter < prog->depth)
	{
		xtemp = z.a * z.a - z.b * z.b + p.a;
		z.b = 2 * z.a * z.b + p.b;
		z.a = xtemp;
		iter++;
	}
	if (iter < prog->depth)
		trans_iter(z, &iter);
	if (iter != prog->depth)
		return prog->color_map[iter % 16] * prog->range_shift_color;
	return 0;
}
