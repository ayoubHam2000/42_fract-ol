/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_pixel_put.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:43:05 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/10 11:44:08 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    ft_put_pixel(SDL_Surface* surface, unsigned int x, unsigned int y, unsigned int color)
{
	if (y >= (unsigned int)surface->h || x >= (unsigned int)surface->w)
			return ;
	*((Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel)) = color;
}
