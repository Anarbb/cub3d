/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:34:22 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/06/13 18:41:05 by aarbaoui         ###   ########.fr       */
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
#include <limits.h>
# define WIDTH 1440
# define HEIGHT 1080
# define FOV 1.0472        // Field of View (60 degrees in radians)
# define NUM_RAYS WIDTH
# define TILE_SIZE 32
# define PLAYER_SIZE 5
# define SENSE 0.3


typedef struct s_var
{
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
	int				left_cell_x;
	int				right_cell_x;
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

	int state;
	
	int offset_x;
	int offset_y;
	int dist_from_top;
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
	
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;

	unsigned int	tex_NO[10000000];
	unsigned int	tex_SO[10000000];
	unsigned int	tex_WE[10000000];
	unsigned int	tex_EA[10000000];
}					t_data;

// raycasting
void    raycasting(t_data *data);
void    horz_caluls(t_engine *p, t_data *data, float ray_angle);
void    get_horz(t_engine *p, t_data *data, float ray_angle);
void    vert_claculs(t_engine *p, t_data *data, float ray_angle);
void    get_vert(t_engine *p, t_data *data, float ray_angle);
void    do_it(t_data *data, float ray_angle, t_engine *p);
int 	hasWallAt(t_data *data, float x, float y);
float 	get_distance(float x1, float y1, float x2, float y2);
float   normalizeAngle(float angle);
void    init_ray_dirs(t_engine *p, float ray_angle);
void    get_offset(t_engine *p, t_data *data);

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