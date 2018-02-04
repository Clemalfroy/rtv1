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
#include <pthread.h>

# define EPSILON pow(10,-6)
# define PI 3.141592653
# define ABS(x) ((x) < 0 ? -(x) : (x))
# define WTH 1450
# define HGT 1450
# define SIGN(a) (a < 0 ? -1 : 1)
# define MAX(x, y) ((x) < (y) ? (y) : (x))
#define RGB(r,g,b) (((char)(r)|((int)((char)(g))<<8))|(((long)(char)(b))<<16))
# define THREADS 16

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_rot
{
	double		j;
	double		p;
	double		y;
}				t_rot;

typedef struct	s_mat
{
	int			ex;
	t_vec3		r1;
	t_vec3		r2;
	t_vec3		r3;
}				t_mat;

typedef struct	s_ray
{
	t_vec3		dir;
	t_vec3		pos;
}				t_ray;

typedef struct	s_light
{
	t_vec3		hit;
	t_vec3		nrm;
	t_vec3		pos;
	t_ray		shd;
}				t_light;

typedef struct	s_cam
{
	t_vec3		pos;
	t_rot		rot;
	t_mat		mat;
}				t_cam;

typedef struct	s_shape
{
	double		radius;
	t_vec3		center;
	t_vec3		color;
	t_vec3		norm;
	t_mat		inv;
	t_mat		rot;
	int			type;
}				t_shape;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_img
{
	void		*img;
	char 		*i_img;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_env
{
	t_mlx		mlx;
	t_img		img;
	t_shape		*shapes;
	t_light		light;
	t_cam		cam;
	t_ray		ray;

	double		tmin;
	double		fov;
	int			hit;
	int			shd;
	int			last;
	int 		nbshape;
	int 		current;
	int			redraw;
}				t_env;

typedef struct	s_thread
{
	int			begin;
	int			end;
	t_env		env;
}				t_thread;

/*
 ** Draw
 */

extern void		putpixel(t_env *env, int x, int y, int color);

/*
 ** Event handling
*/

extern int		e_keyrelease(int key, t_env *env);
extern int		e_destroy(t_env *env);
extern int		e_loophook(t_env *env);
extern int		e_expose(t_env *env);
extern void		compute(t_env *env);

/*
 ** Vectors functions
*/

extern double	vec3_scale(t_vec3 v1, t_vec3 v2);
extern double	vec3_getdst(t_vec3 vec);
extern t_vec3	vec3_new(double x, double y, double z);
extern t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
extern t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
extern t_vec3	vec3_divnorm(t_vec3 vec, double k);
extern t_vec3	vec3_dot(t_vec3 v, double k);
extern t_vec3	vec3_normalize(t_vec3 vec);
extern t_vec3	vec3_neg(t_vec3 vec);

/*
 ** Rotation handlers
*/

extern t_vec3	rotate(t_vec3 vec, t_mat mat);
extern t_ray	rotateray(t_ray ray, t_mat mat);
extern t_vec3	rotatecam(t_vec3 vec, t_mat mat);
extern void		translate(t_vec3 *vec, t_vec3 trs);

/*
 ** Matrix handlers
*/

extern t_mat	matrix_x(double t);
extern t_mat	matrix_y(double t);
extern t_mat	matrix_z(double t);

extern double	matrix_det(t_mat mat);
extern t_mat	matrix_inv(t_mat mat);
extern t_mat	matrix_mult(t_mat m1, t_mat m2);
extern t_mat	matrix_cam(t_rot rot);

/*
 ** Hit handlers
*/

extern int		rt_hitcone(t_shape obj, t_ray ray, double *t);
extern int		rt_hitsphere(t_shape obj, t_ray ray, double *t);
extern int		rt_hitcylinder(t_shape obj, t_ray ray, double *t);
extern int		rt_hitplane(t_shape obj, t_ray ray, double *t);

extern int		rt_solvesphquadra(t_shape obj, t_ray ray, double *t1, double *t2);
extern int		rt_solvecylquadra(t_shape obj, t_ray ray, double *t1, double *t2);
extern int		rt_solveconquadra(t_shape obj, t_ray ray, double *t1, double *t2);

/*
 ** light functions
 */

extern double	lb_light(t_env *env);

/*
 ** Create objects functions
*/

extern t_shape	*shape(t_env *env);

/*
 ** Color function
*/

extern int		rgbtoint(t_vec3 color);

/*
 * exit
*/

void 			mlx_exit(t_env *env, int code);

#endif
