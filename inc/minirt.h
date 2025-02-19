/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:43 by amylle            #+#    #+#             */
/*   Updated: 2025/02/07 18:38:18 by bclaeys          ###   ########.fr       */
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
	SPHERE,
	PLANE,
	CYLINDER
}	t_shape_type;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_hit
{
	t_vector		nhit;
	t_vector		phit;
	t_color			color;
	float			t;
	struct s_shape	*shape;
}					t_hit;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_camera
{
	bool		initialized;
	t_vector	pos;
	t_vector	direction;
	float		scale;
	float		ratio;
	float		cam_matrix[4][4];
	float		angle_updown;
	float		angle_leftright;
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
	t_color		color;
	float		rad_sq;
	t_vector	l_cache;
	bool		cache_valid;
}				t_sphere;

//direction here is the normalized normal vector of the plane
//which means its perpendicular to the plane with len 1
typedef struct s_plane
{
	t_vector	pos;
	t_vector	direction;
	t_color		color;
	float		numerator_cache;
	bool		cache_valid;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	pos;
	t_vector	direction;
	float		diameter;
	float		height;
	t_color		color;
	t_vector	base;
	t_vector	origin_to_cylbase;
	t_vector	origin_perp_to_cylbase;
	float		rad_sq;
}				t_cylinder;

typedef union s_shape_union
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_shape_union;

typedef struct s_shape
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

int			parse_file(t_rt	*obj, char *filename);
int			parse_vector(char *str, t_vector *vec);
int			parse_color(char *str, t_color *col);
int			parse_sphere(t_rt *obj, char *line, char **args);
int			parse_plane(t_rt *obj, char *line, char **args);
int			parse_cylinder(t_rt *obj, char *line, char **args);
int			parse_ambient(t_rt *obj, char *line, char **args);
int			parse_camera(t_rt *obj, char *line, char **args);
int			parse_light(t_rt *obj, char *line, char **args);
int			parse_ratio(char *str, float *ra);
void		shapeadd_back(t_shape	**root, t_shape *shape);

int			ft_error(char *str, char *filename);
void		free_shapes(t_shape *shapes);
void		my_pixel_put(t_mlx *mlx, int x, int y, int color);
void		ft_freestrarray(char **strarray);
int			ft_atoi_base(char *num, char *base);
int			ft_atoi_base(char *num, char *base);
void		ft_put_new_img(t_rt *obj);
int			ft_keypress(int keycode, void *param);
int			ft_close_win(void *param);

int			ft_lerp(int start, int end, double percent);
int			interpol_color(int scolor, int ecolor, double percent);
t_color		set_color(int r, int g, int b);
int			rgb_to_int(int r, int g, int b);
int			convert_color(t_color color);
int			add_color(t_hit *hit, float operatee,
				t_color orig_col, char operator);
void		cap_ambient(t_hit *hit);

bool		intersect(t_ray *ray, t_shape *shape, float *t);
void		ft_swapf(float *nptr1, float *nptr2);
t_vector	localize_cylinder_pos(t_vector pos);
t_vector	localize_cylinder_direction(t_vector direction);
bool		intersect_cylinder(t_ray *ray, t_cylinder *cyl, float *t);

t_vector	calc_nhit_sphere(t_vector *phit, t_sphere *sph, t_vector *ray_dir);
t_vector	calc_nhit_plane(t_plane *plane, t_vector *ray_dir);
t_vector	calc_nhit_cylinder(t_vector *phit, t_cylinder *cyl,
				t_vector *ray_d);

void		make_camera_ray(t_rt *obj, int x, int y, t_vector *cam_dir);
void		make_cam_matrix(t_camera *camera);
void		render(t_rt *obj);
t_vector	localize_cylinder_ray(t_vector ray);

/* void	ft_left_rotate(void	*param); */
/* void	ft_right_rotate(void	*param); */
/* void	ft_up_rotate(void	*param); */
/* void	ft_down_rotate(void	*param); */
void		ft_rotate_x_axis(void *param, double angle);
void		ft_rotate_y_axis(void *param, double angle);
void		ft_adjust_zoom(void *param, float zoom_lvl);

#endif 
