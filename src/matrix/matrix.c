/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline t_mat		matrix_x(double t)
{
	t_mat	mat;

	mat.r1 = vec3_new(1, 0, 0);
	mat.r2 = vec3_new(0, cos(t), -sin(t));
	mat.r3 = vec3_new(0, sin(t), cos(t));
	mat.ex = 1;
	return (mat);
}

inline t_mat		matrix_y(double t)
{
	t_mat	mat;

	mat.r1 = vec3_new(cos(t), 0, sin(t));
	mat.r2 = vec3_new(0, 1, 0);
	mat.r3 = vec3_new(-sin(t), 0, cos(t));
	mat.ex = 1;
	return (mat);
}

inline t_mat		matrix_z(double t)
{
	t_mat	mat;

	mat.r1 = vec3_new(cos(t), -sin(t), 0);
	mat.r2 = vec3_new(sin(t), cos(t), 0);
	mat.r3 = vec3_new(0, 0, 1);
	mat.ex = 1;
	return (mat);
}