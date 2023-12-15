/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:18:09 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/14 17:37:47 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <float.h>
# include <pthread.h>

# include "structs.h"
# include "utils.h"
# include "events.h"
# include "colors.h"
# include "trace_ray.h"
# include "lighting.h"
# include "get_objs.h"

# define B_EXIT 17

#endif