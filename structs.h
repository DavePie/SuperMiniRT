/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:47:35 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 12:13:31 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2
# define SPHERE 3
# define PLANE 4
# define CYLINDER 5
# define INIT_WIDTH 800
# define INIT_HEIGHT 500


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

typedef struct s_scene
{
	t_obj	*ambient;
	t_obj	*camera;
	t_obj	*lights;
	t_obj	*objects;
	t_mlx	*mlx;
	int		exit_code;
}													t_scene;


#endif