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
# define WINDOWWIDTH 1920
# define WINDOWHEIGHT 1080

typedef enum s_shape_type
{
	sphere
}	t_shape_type;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;

typedef struct s_camera
{
	bool		initialized;
	t_vector	pos;
	t_vector	direction;
	size_t		fov;
}		t_camera;

typedef struct s_sphere
{
	t_vector	pos;
	float		diameter;
	int			color;
}				t_sphere;

typedef union s_shape_union
{
	t_sphere	sphere;
}	t_shape_union;

typedef	struct s_shape
{
	t_shape_type 	type;
	t_shape_union	shape;
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
	t_mlx		mlx;
	t_camera	camera;
}				t_rt;

void	ft_error(char *str);
void	my_pixel_put(t_mlx *mlx, int x, int y, int color);
void	ft_freestrarray(char **strarray);
t_point	project(int x, int y, t_rt *obj);
int		ft_atoi_base(char *num, char *base);
int		ft_atoi_base(char *num, char *base);
void	ft_put_new_img(t_rt *obj);
int		ft_keypress(int keycode, void *param);
int		ft_close_win(void *param);

int	ft_lerp(int start, int end, double percent);
int	interpol_color(int scolor, int ecolor, double percent);

#endif 
