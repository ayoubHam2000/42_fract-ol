/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:01:53 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:46:41 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "complex.h"
# include <SDL2/SDL.h>

# define TITLE "fractol"
# define TRAN 0.1
# define CZOOM 0.2

# define KEY_L SDL_SCANCODE_LEFT
# define KEY_R SDL_SCANCODE_RIGHT
# define KEY_U SDL_SCANCODE_UP
# define KEY_D SDL_SCANCODE_DOWN
# define KEY_A SDL_SCANCODE_A
# define KEY_ESC SDL_SCANCODE_ESCAPE

typedef double t_double;

typedef struct s_complex
{
	t_double	a;
	t_double	b;
}	t_complex;

typedef struct s_graph
{
	t_complex		x_bound;
	t_complex		y_bound;
	t_double		zoom;
	t_double		step_x;
	t_double		step_y;
}	t_graph;

typedef struct s_prog	t_prog;
struct s_prog
{
	SDL_Window		*win;
	int						w_size;
	int						depth;
	SDL_Surface		*img;
	t_complex			julia_const;
	t_graph				g;
	int						color_map[16];
	double				range_shift_color;
	int						quit;
	int						mx;
	int						my;
	int		(*f)(t_prog *prog, t_double x, t_double y);
} ;



t_prog	*init_prog(void);
void	*init_sdl(t_prog *prog);

int		on_mouse_wheel(int button, t_prog *prog);
int		on_key_up(int keycode, t_prog *prog);

void	init_graph(t_graph *g, int w_size);
void	graph_loop(t_prog *prog);

int		mandelbrot_set(t_prog *prog, t_double x, t_double y);
int		julia_set(t_prog *prog, t_double x, t_double y);
int		bonus_fract(t_prog *prog, t_double x, t_double y);
void  on_mouse_move(int x, int y, t_prog *prog);

void	get_colors(int *map);
double	ft_atof(const char *str);
void	ft_put_str(char *str);
void    ft_put_pixel(SDL_Surface* surface, unsigned int x, unsigned int y, unsigned int color);
int		ft_atoi(const char *str);
void	*update_window(t_prog *prog);
int		exit_fractol(t_prog *prog);
void	check_args(int ac, char **av);

#endif
