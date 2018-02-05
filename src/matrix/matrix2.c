/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline double		matrix_det(t_mat mat)
{
	double	res;

	res = 0;
	res += mat.r1.x * mat.r2.y * mat.r3.z;
	res += mat.r2.x * mat.r3.y * mat.r1.z;
	res += mat.r3.x * mat.r1.y * mat.r2.z;
	res -= mat.r1.x * mat.r3.y * mat.r2.z;
	res -= mat.r3.x * mat.r2.y * mat.r1.z;
	res -= mat.r2.x * mat.r1.y * mat.r3.z;
	return (res);
}

inline t_mat		matrix_inv(t_mat mat)
{
	t_mat	res;
	double	det;

	det = matrix_det(mat);
	if (det)
	{
		res.r1 = vec3_new((mat.r2.y * mat.r3.z)
			- (mat.r2.z * mat.r3.y), (mat.r1.z * mat.r3.y)
			- (mat.r1.y * mat.r3.z), (mat.r1.y * mat.r2.z)
			- (mat.r1.z * mat.r2.y));
		res.r2 = vec3_new((mat.r2.z * mat.r3.x)
			- (mat.r2.x * mat.r3.z), (mat.r1.x * mat.r3.z)
			- (mat.r1.z * mat.r3.x), (mat.r1.z * mat.r2.x)
			- (mat.r1.x * mat.r2.z));
		res.r3 = vec3_new((mat.r2.x * mat.r3.y)
			- (mat.r2.y * mat.r3.x), (mat.r1.y * mat.r3.x)
			- (mat.r1.x * mat.r3.y), (mat.r1.x * mat.r2.y)
			- (mat.r1.y * mat.r2.x));
		res.r1 = vec3_dot(res.r1, 1.0 / det);
		res.r2 = vec3_dot(res.r2, 1.0 / det);
		res.r3 = vec3_dot(res.r3, 1.0 / det);
	}
	res.ex = 1;
	return (res);
}

inline t_mat		matrix_mult(t_mat m1, t_mat m2)
{
	t_mat	res;
	double	a;
	double	b;
	double	c;

	a = (m1.r1.x * m2.r1.x) + (m1.r1.y * m2.r2.x) + (m1.r1.z * m2.r3.x);
	b = (m1.r1.x * m2.r1.y) + (m1.r1.y * m2.r2.y) + (m1.r1.z * m2.r3.y);
	c = (m1.r1.x * m2.r1.z) + (m1.r1.y * m2.r2.z) + (m1.r1.z * m2.r3.z);
	res.r1 = vec3_new(a, b, c);
	a = (m1.r2.x * m2.r1.x) + (m1.r2.y * m2.r2.x) + (m1.r2.z * m2.r3.x);
	b = (m1.r2.x * m2.r1.y) + (m1.r2.y * m2.r2.y) + (m1.r2.z * m2.r3.y);
	c = (m1.r2.x * m2.r1.z) + (m1.r2.y * m2.r2.z) + (m1.r2.z * m2.r3.z);
	res.r2 = vec3_new(a, b, c);
	a = (m1.r3.x * m2.r1.x) + (m1.r3.y * m2.r2.x) + (m1.r3.z * m2.r3.x);
	b = (m1.r3.x * m2.r1.y) + (m1.r3.y * m2.r2.y) + (m1.r3.z * m2.r3.y);
	c = (m1.r3.x * m2.r1.z) + (m1.r3.y * m2.r2.z) + (m1.r3.z * m2.r3.z);
	res.r3 = vec3_new(a, b, c);
	res.ex = 1;
	return (res);
}

inline t_mat		matrix_cam(t_vec3 rot)
{
	t_mat	mat;

	mat.r1 = vec3_new(-cos(rot.y) * sin(rot.x), cos(rot.x),
		sin(rot.y) * sin(rot.x));
	mat.r2 = vec3_new(sin(rot.y), 0, cos(rot.y));
	mat.r3 = vec3_new(cos(rot.y) * cos(rot.x), sin(rot.x),
		-sin(rot.y) * cos(rot.x));
	mat.ex = 1;
	return (mat);
}