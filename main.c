/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:35:22 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:56:48 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractol_frame(t_prog *prog)
{
	SDL_FillRect(prog->img, NULL, SDL_MapRGB(prog->img->format, 0, 0, 0));
	// change_graph(&(prog->g), prog->w_size);
	graph_loop(prog);
	update_window(prog);
}

void	fractol_loop(t_prog *prog)
{
	SDL_Event e;

	while (!prog->quit)
	{
		fractol_frame(prog);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				prog->quit = 1;
			else if (e.type == SDL_KEYUP)
				on_key_up(e.key.keysym.scancode, prog);
			else if (e.type == SDL_MOUSEWHEEL)
				on_mouse_wheel(e.wheel.y, prog);
			else if (e.type == SDL_MOUSEMOTION)
				on_mouse_move(e.motion.x, e.motion.y, prog);
		}
	}
}

void	fractol_init(int ac, char **av, t_prog *prog)
{
	if (ft_atoi(av[3]) == 1)
		prog->f = mandelbrot_set;
	else if (ft_atoi(av[3]) == 2)
		prog->f = julia_set;
	else if (ft_atoi(av[3]) == 3)
		prog->f = bonus_fract;
	if (ac >= 5)
		prog->julia_const.a = ft_atof(av[4]);
	if (ac >= 6)
		prog->julia_const.b = ft_atof(av[5]);
	init_graph(&(prog->g), prog->w_size);
}

int	main(int ac, char **av)
{
	t_prog		*prog;

	check_args(ac, av);
	prog = init_prog();
	if (!prog)
		return (1);
	prog->w_size = ft_atoi(av[1]);
	prog->depth = ft_atoi(av[2]);
	if (!init_sdl(prog))
		return (1);
	fractol_init(ac, av, prog);
	fractol_loop(prog);
	return (0);
}
