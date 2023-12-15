/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:47:35 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/15 14:08:36 by dvandenb         ###   ########.fr       */
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

# define K_ESC 53

# include <pthread.h>

typedef struct s_p
{
	float	x;
	float	y;
	float	z;
}													t_p;

typedef struct s_obj
{
	int				type;
	unsigned int	color;
	struct s_obj	*next;
	t_p				*p;
	t_p				*v;
	float			w;
	float			h;
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

typedef struct s_threads t_threads;

typedef struct s_scene
{
	t_obj	*ambient;
	t_obj	*camera;
	t_obj	*lights;
	t_obj	*objects;
	t_mlx	*mlx;
	int		exit_code;
	t_threads	*multi_t;
}													t_scene;

struct s_threads
{
	pthread_t	pids[NUM_THREADS];
	int			*cur_x;
	pthread_mutex_t	*l;
	int			*do_exit;
};
#endif