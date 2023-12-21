/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:47:35 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/21 17:51:38 by dvandenb         ###   ########.fr       */
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

# ifdef LINUX
#  define LJ_UP 111
#  define LJ_DOWN 112
#  define LJ_LEFT 232
#  define LJ_RIGHT 65111
#  define RJ_UP 65293
#  define RJ_DOWN 65507
#  define RJ_LEFT 97
#  define RJ_RIGHT 115
#  define LS 100
#  define RS 102
#  define K_LEFT 65361
#  define K_RIGHT 65363
#  define K_DOWN 65364
#  define K_UP 65362
#  define K_ESC 65307
#  define K_W 119
#  define K_A 97
#  define K_S 115
#  define K_D 100
# else
#  define LINUX 0
#  define LJ_UP 0
#  define LJ_DOWN 0
#  define LJ_LEFT 0
#  define LJ_RIGHT 0
#  define RJ_UP 65293
#  define RJ_DOWN 65507
#  define RJ_LEFT 97
#  define RJ_RIGHT 115
#  define LS 0
#  define RS 0
#  define K_LEFT 123
#  define K_RIGHT 124
#  define K_DOWN 125
#  define K_UP 126
#  define K_ESC 53
#  define K_W 13
#  define K_A 0
#  define K_S 1
#  define K_D 2
# endif

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
	int				*type;
	unsigned int	*color;
	struct s_obj	*next;
	t_p				*p;
	t_p				*v;
	float			*w;
	float			*h;
	float			*specular;
	float			*reflect;
	t_img			*i;
	t_img			*b;
	int				*distrupt;
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
