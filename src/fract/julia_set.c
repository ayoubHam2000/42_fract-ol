/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:24:08 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:43:01 by aben-ham         ###   ########.fr       */
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

int	julia_set(t_prog *prog, t_double x, t_double y)
{
	t_complex		z;
	int				iter;
	t_double		xtemp;
	t_complex  p;

	p.a = x;
	p.b = y;
	z = p;
	iter = 0;
	while (z.a * z.a + z.b * z.b <= (1 << 16) && iter < prog->depth)
	{
		xtemp = z.a * z.a - z.b * z.b + prog->julia_const.a;
		z.b = 2 * z.a * z.b + prog->julia_const.b;
		z.a = xtemp;
		iter++;
	}
	if (iter < prog->depth)
		trans_iter(z, &iter);
	return prog->color_map[iter % 16] * prog->range_shift_color;
}
