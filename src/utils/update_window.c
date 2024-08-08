/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:15:03 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:39:52 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void  *update_window(t_prog *prog)
{
  SDL_UpdateWindowSurface(prog->win);
  return (prog);
}
