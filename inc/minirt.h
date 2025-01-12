/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:43 by amylle            #+#    #+#             */
/*   Updated: 2024/06/11 12:27:16 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include "../mlx/mlx.h"
# include <math.h>
# include "../src/vector/vector.h"
# include <stdbool.h>
# include <stdio.h>
# define WINDOWWIDTH 1920
# define WINDOWHEIGHT 1080

typedef enum s_shape_type
{
	sphere,
	plane,
	cylinder
}	t_shape_type;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_camera
{
	bool		initialized;
	t_vector	pos;
	t_vector	direction;
	int			fov;
}				t_camera;

//ambient light struct
typedef struct s_ambient
{
	bool		initialized;
	float		ratio;
	t_color		color;
}				t_ambient;

typedef struct s_light
{
	bool		initialized;
	t_vector	pos;
	float		brightness;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector	pos;
	float		diameter;
	t_color			color;
}				t_sphere;

//direction here is the normalized normal vector of the plane
//which means its perpendicular to the plane with len 1
typedef struct s_plane
{
	t_vector	pos;
	t_vector	direction;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	normal;
	float		diameter;
	float		height;
	t_color		color;
}				t_cylinder;

typedef union s_shape_union
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_shape_union;

typedef	struct s_shape
{
	t_shape_type	type;
	t_shape_union	shape;
	struct s_shape	*next;
}					t_shape;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx;

typedef struct s_rt
{
	t_mlx			mlx;
	t_camera		camera;
	t_ambient		ambient;
	t_light			light;
	t_shape			*shapes;
}					t_rt;

int	parse_file(t_rt	*obj, char *filename);

int		ft_error(char *str, char *filename);
void	my_pixel_put(t_mlx *mlx, int x, int y, int color);
void	ft_freestrarray(char **strarray);
int		ft_atoi_base(char *num, char *base);
int		ft_atoi_base(char *num, char *base);
void	ft_put_new_img(t_rt *obj);
int		ft_keypress(int keycode, void *param);
int		ft_close_win(void *param);

int	ft_lerp(int start, int end, double percent);
int	interpol_color(int scolor, int ecolor, double percent);
int	rgb_to_int(int r, int g, int b);

#endif 
