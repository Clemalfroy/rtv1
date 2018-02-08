/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1/libmlx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:52:16 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/13 15:38:53 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_LIBMLX_H
# define RTV1_LIBMLX_H

# include <mlx.h>
# include <libft.h>

# define RGB(r,g,b) (((char)(r)|((int)((char)(g))<<8))|(((long)(char)(b))<<16))

# define MSP mlx_string_put
# define WTH 1000
# define HGT 1000
# define HUDX WTH + 10
# define WHITE 0x0FFFFFF
# define BLACK 0x000000
# define GRAY 0x686868

struct s_env;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

extern void		mlx_hud(struct s_env *e);
extern void		putpixel(struct s_env *env, int x, int y, int color);
extern int		rgbtoint(t_vec3 color);
void			mlx_exit(struct s_env *env, int code);

#endif
