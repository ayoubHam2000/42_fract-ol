/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:54:43 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:39:42 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_prog	*init_prog(void)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->julia_const.a = 0;
	prog->julia_const.b = 0;
	prog->range_shift_color = 1;
	prog->quit = 0;
	get_colors(prog->color_map);
	prog->f = NULL;
	return (prog);
}

void    *init_sdl(t_prog *prog)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return NULL;
  SDL_Window* window = SDL_CreateWindow(
    TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    prog->w_size, prog->w_size, SDL_WINDOW_SHOWN);
  if (window == NULL)
      return NULL;
  prog->win = window;
  prog->img = SDL_GetWindowSurface(prog->win);
  return prog;
}

void	init_graph(t_graph *g, int w_size)
{
	g->zoom = 1;
	g->x_bound.a = -2;
	g->x_bound.b = 2;
	g->y_bound.a = -2;
	g->y_bound.b = 2;
	g->step_x = (g->x_bound.b - g->x_bound.a) / w_size;
	g->step_y = (g->y_bound.b - g->y_bound.a) / w_size;
}
