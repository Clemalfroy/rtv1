/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/math/v3.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:28:45 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:34:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_V3_H
# define LIBFT_MATH_V3_H

# include <math.h>

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

extern t_vec3		ft_v3(float x, float y, float z);
extern t_vec3		ft_v3add(t_vec3 a, t_vec3 b);
extern t_vec3		ft_v3sub(t_vec3 a, t_vec3 b);
extern t_vec3		ft_v3mul(t_vec3 a, t_vec3 b);
extern t_vec3		ft_v3div(t_vec3 a, t_vec3 b);
extern float	ft_v3dot(t_vec3 a, t_vec3 b);
extern float	ft_v3ang(t_vec3 a, t_vec3 b);
extern float	ft_v3len(t_vec3 a);
extern t_vec3		ft_v3nor(t_vec3 a);

#endif
