/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:08:51 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:39 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	is_blank(char c)
{
	if (c == ' ' || c == '\f'
		|| c == '\v' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

static double	ft_atof_p(const char *str)
{
	double	res;
	int		e;

	res = 0.0;
	e = 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		e *= 10;
		str++;
	}
	res = res / e;
	return (res);
}

double	ft_atof(const char *str)
{
	double	res;
	int		signe;

	while (is_blank(*str))
		str++;
	signe = 1;
	if (*str == '-')
		signe = -1;
	if (*str == '+' || *str == '-')
		str++;
	res = 0.0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
		res += ft_atof_p(++str);
	return (res * signe);
}
