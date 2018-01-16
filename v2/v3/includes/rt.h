/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:39:10 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 13:35:33 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include "../libft/includes/libft.h"
#include "mlx.h"
#include "utility.h"
#include <math.h>
#include <limits.h>
#include <float.h>

# define ABS(x) ((x) < 0 ? -(x) : (x))
# define WTH 1450
# define HGT 1450
# define MAX(x, y) ((x) < (y) ? (y) : (x))

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_camera
{
	t_vec3		cam_pos;
	t_vec3		view_drt;
	float		screen_dst;

	t_vec3		screen_center;
	t_vec3		p0;
	t_vec3		p1;
	t_vec3		p2;
}				t_camera;

typedef struct	s_plane
{
	t_vec3		position;
	t_vec3		normal;
}				t_plane;

typedef struct	s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	double		u;
	double		v;
	double		w;
}				t_triangle;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_vec3		color;
}				t_sphere;

union u_shape
{
	t_plane p;
	t_sphere s;
	t_triangle t;
};

enum e_kind
{
	SHAPE_SPHERE, SHAPE_TRIANGLE, SHAPE_PLANE
};

typedef struct		s_shape
{
	union u_shape	shape;
	enum e_kind		kind;
	t_vec3			color;
}					t_shape;

typedef struct	s_env
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*i_img;
	int			size_l;
	int			bpp;
	int			endian;

	t_camera	camera;
}				t_env;

extern t_vec3	ft_vec3(float x, float y, float z);
extern t_vec3	ft_vec3_add(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_cross(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_sub(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_mul(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_div(t_vec3 a, t_vec3 b);
extern t_vec3	ft_vec3_times(t_vec3 a, double nb);
extern t_vec3	ft_vec3_divnb(t_vec3 a, double nb);
extern float	ft_vec3_dot(t_vec3 a, t_vec3 b);
extern float	ft_vec3_ang(t_vec3 a, t_vec3 b);
extern float	ft_vec3_len(t_vec3 a);
extern t_vec3	ft_vec3_nor(t_vec3 a);
extern t_vec3 ft_vec3_normalize(t_vec3 vec);

extern void		ft_sphere_cnstr(t_sphere *sphere, t_vec3 c, double radius);
extern void		ft_plane_cnstr(t_plane *plane, t_vec3 pos, t_vec3 norm);
extern void		ft_triangle_cnstr(t_triangle *t, t_vec3 a, t_vec3 b, t_vec3 c);

t_vec3			triangle_calculate_normal(t_triangle *t, int *shininess,
		t_vec3 *specularcolor);
t_vec3			sphere_calculate_normal(t_sphere *s, t_vec3 p0, int* shininess,
		t_vec3 *specularcolor);
t_vec3			plane_calculate_normal(t_plane *plane, int *shininess,
		t_vec3 *specularcolor, t_vec3 colour);
t_vec3			shape_calculate_normal(t_shape *sp, t_vec3 p0, t_vec3 *s, int *si);
void		shape_assoc_sphere(t_shape *shape, t_sphere s, t_vec3 c);
void		shape_assoc_triangle(t_shape *shape, t_triangle t, t_vec3 c);
void		shape_assoc_plane(t_shape *shape, t_plane p, t_vec3 c);

double		ft_max(double a, double b);
int				ray_sphere_intersect(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_direction, double *t);
int				ray_plane_intersect(t_plane *plane, t_vec3 rayo, t_vec3 rd, double *t);
int				ray_triangle_intersect(t_triangle *plane, t_vec3 rayo, t_vec3 rd, double *t);
int				ray_shape_intersect(t_shape *s, t_vec3 ro, t_vec3 rd, double *t);
double		ft_color(t_vec3 color);
int				ft_keyrelease(int key, t_env *env);
int				ft_destroy(t_env *env);

#endif
