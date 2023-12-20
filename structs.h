/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:47:35 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 14:17:56 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define SPECIAL 3
# define AMBIENT 4
# define CAMERA 5
# define LIGHT 6

# define INIT_WIDTH 1600
# define INIT_HEIGHT 1000

# define Z_OFFSET 1

# define NUM_THREADS 12

# define K_LEFT 123
# define K_RIGHT 124
# define K_DOWN 125
# define K_UP 126
# define K_ESC 53
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2

# define CHECKERBOARD 1

# include <pthread.h>

typedef struct s_p
{
	float	x;
	float	y;
	float	z;
}													t_p;

typedef struct s_c
{
	int	x;
	int	y;
	int z;
}													t_c;

typedef struct s_img
{
	void	*img;
	char	*pix;
	int		w;
	int		h;
}													t_img;

typedef struct s_obj
{
	int				type;
	unsigned int	color;
	struct s_obj	*next;
	t_p				*p;
	t_p				*v;
	float			w;
	float			h;
	float			specular;
	float			reflect;
	t_img			*i;
	t_img			*b;
	int				distrupt;
}													t_obj;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buffer;
	char	*pix;
	int		width;
	int		height;
}													t_mlx;

typedef struct s_threads
{
	pthread_t		pids[NUM_THREADS];
	int				*cur_x;
	pthread_mutex_t	*l;
	int				do_exit;
}													t_threads;

typedef struct s_scene
{
	t_obj		*ambient;
	t_obj		*camera;
	t_obj		*lights;
	t_obj		*objects;
	t_mlx		*mlx;
	int			exit_code;
	t_threads	*multi_t;
	t_p			o_x;
	t_p			o_y;
}													t_scene;
#endif
