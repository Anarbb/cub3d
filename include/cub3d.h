/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/13 12:37:59 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
#include <limits.h>
# define WIDTH 1440
# define HEIGHT 1080
# define FOV 1.0472        // Field of View (60 degrees in radians)
# define NUM_RAYS WIDTH
# define TILE_SIZE 32

typedef struct s_ray
{
	mlx_image_t		*img;
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
}	t_ray;

typedef struct s_line
{
	int				x0;
	int				x1;
	int				x2;
	int				x3;

	int				y0;
	int				y1;
	int				y2;
	int				y3;

	int				size;
}					t_line;

typedef struct s_var
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	int				i;
	int				j;
	int				l;
	int				x;
	int				y;
	int				k;

	int is_ray_facing_down;
    int is_ray_facing_up;
    int is_ray_facing_right;
    int is_ray_facing_left;

	float			speed;
	float			new_px;
	float			new_py;
	int				cell_x;
	int				cell_y;
}					t_var;

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
	int is_ray_facing_down;
    int is_ray_facing_up;
    int is_ray_facing_right;
    int is_ray_facing_left;
    float distance;
    int h;
    int v;

    float hit_x;
    float hit_y;

    float x_step_h;
    float y_step_h;

    float x_intercept_h;
    float y_intercept_h;


	float x_step_v;
    float y_step_v;

    float x_intercept_v;
    float y_intercept_v;

    float hit_v_x;
    float hit_v_y;

    float hit_h_x;
    float hit_h_y;

	float distance_h;
	float distance_v;

	float wall_hight;
	
	float angle;
	float dist ;
	
	float wall_top;
	float wall_bottom;

}					t_engine;

typedef struct s_world
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*floor_c;
	char			*ceil_c;
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
	t_engine		eng;
	t_player		pl;
	t_world			world;
	t_var			vr;
	t_ray			rays[NUM_RAYS];
	// mlx_texture_t	*NO;
	// mlx_texture_t	*SO;
	// mlx_texture_t	*WE;
	// mlx_texture_t	*EA;
	// unsigned int	tex_NO[10000000];
	// unsigned int	tex_SO[10000000];
	// unsigned int	tex_WE[10000000];
	// unsigned int	tex_EA[10000000];
}					t_data;

// raycasting
void    raycasting(t_data *data);

// parsing
void				init_parse(t_data *data, char *map_fi);
// utils
void mlx_draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, int color);
int					is_map(char *line);
int					get_step(float x);
int					get_rgba(int r, int g, int b, int a);
int					get_rgb(int r, int g, int b);
void				free_all(char **s);
int					ft_strcmp(char *s1, char *s2);
void				calculate_map_dimensions(t_data *data);
void				ft_error(char *str);
#endif