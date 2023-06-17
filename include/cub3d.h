/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/17 10:31:21 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define WIDTH 1440
# define HEIGHT 1080
# define FOV 1.0472
# define NUM_RAYS WIDTH
# define TILE_SIZE 32
# define PLAYER_SIZE 5
# define SENSE 0.3
# define RENDER_DISTANCE 1000

typedef struct s_line
{
	int	x0;
	int	x1;
	int	x2;
	int	x3;

	int	y0;
	int	y1;
	int	y2;
	int	y3;
	int	size;
}		t_line;

typedef struct s_var
{
	int		i;
	int		j;
	int		l;
	int		x;
	int		y;
	int		k;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;

	float	speed;
	float	new_px;
	float	new_py;
	int		cell_x;
	int		cell_y;
	int		left_cell_x;
	int		right_cell_x;
}			t_var;

typedef struct s_player
{
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			pa;
	mlx_image_t		*img;
}					t_player;

typedef struct s_engine
{
	int				is_ray_facing_down;
	int				is_ray_facing_up;
	int				is_ray_facing_right;
	int				is_ray_facing_left;
	float			distance;
	int				h;
	int				v;

	float			hit_x;
	float			hit_y;

	float			x_step_h;
	float			y_step_h;

	float			x_intercept_h;
	float			y_intercept_h;

	float			x_step_v;
	float			y_step_v;

	float			x_intercept_v;
	float			y_intercept_v;

	float			hit_v_x;
	float			hit_v_y;

	float			hit_h_x;
	float			hit_h_y;

	float			distance_h;
	float			distance_v;

	float			wall_hight;

	float			angle;
	float			dist ;

	float			wall_top;
	float			wall_bottom;

	int				state;

	int				offset_x;
	int				offset_y;
	int				dist_p;
	mlx_texture_t	*img;
	unsigned int	*tex;
	int				color;
}					t_engine;

typedef struct s_world
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor_c;
	char			*ceil_c;
	int				floor;
	int				ceil;
	int				map_width;
	int				map_height;
	mlx_image_t		*walls;
	mlx_image_t		*minim;
	mlx_image_t		*skybox;
	char			**map;
}					t_world;

typedef struct s_data
{
	void			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*line;
	mlx_image_t		*wall;
	mlx_image_t		*crosshair;
	mlx_image_t		*weapon;
	t_engine		eng;
	t_player		pl;
	t_world			world;
	t_var			vr;

	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*crosshair_tex;
	mlx_texture_t	*weapon_tex;

	unsigned int	tex_no[10000000];
	unsigned int	tex_so[10000000];
	unsigned int	tex_we[10000000];
	unsigned int	tex_ea[10000000];

	t_engine		*ray;
}					t_data;

// raycasting
void	raycasting(t_data *data);
void	horz_caluls(t_engine *p, t_data *data, float ray_angle);
void	get_horz(t_engine *p, t_data *data, float ray_angle);
void	vert_claculs(t_engine *p, t_data *data, float ray_angle);
void	get_vert(t_engine *p, t_data *data, float ray_angle);
void	do_it(t_data *data, float ray_angle, t_engine *p);
int		has_wall_at(t_data *data, float x, float y);
float	get_dis(float x1, float y1, float x2, float y2);
float	normalize_angle(float angle);
void	init_ray_dirs(t_engine *p, float ray_angle);
void	get_offset(t_engine *p, t_data *data);
//skybox
void	skybox(t_data *data);
//minimap
void	minimap(t_data *data);
void	mlx_draw_line(mlx_image_t *image, t_line t, int color);
// parsing
void	init_parse(t_data *data, char *map_fi);
void	ft_error(char *str);
int		is_empty(char c);
int		is_valid(t_var *p, char **map);
int		is_surrounded(char **map);
void	parse_params_2(t_data *data, char *line, int *is);
// utils

int		is_map(char *line);
int		get_step(float x);
int		get_rgba(int r, int g, int b, int a);
int		get_rgb(int r, int g, int b);
void	free_all(char **s);
int		ft_strcmp(char *s1, char *s2);
void	calculate_map_dimensions(t_data *data);
void	ft_error(char *str);
void	fill_png(unsigned int *list, mlx_texture_t *png);
int		check_texture(t_data *data);
void	fill_textures(t_data *data);
void	init_start_angle(t_var p, t_data *data);
void	init_player(t_data *data);
void	change_angle(t_data *data);
void	init_cells(t_var *p);
void	check_collision(t_data *data, t_var *p);
void	hook_norm(t_data *data, t_var *p);
void	ft_hook(void *param);

#endif