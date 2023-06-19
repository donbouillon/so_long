/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slistle <slistle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:08:44 by slistle           #+#    #+#             */
/*   Updated: 2023/06/19 22:11:32 by slistle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "get_next_line.h"
#include <fcntl.h>


typedef struct so_long_var_s
{
	char	**map;
	int		x;
	int		y;
	int		map_x;
	int		lines_counter;
	int		lines;
	void	*mlx;
	void	*win;
	void 	*img_wall;
	void 	*img_ground;
	void 	*img_player;
	void	*img_coin;
	void	*img_exit;
	int 	player_x;
	int		player_y;
	int 	moves_counter;
	int		collectibles_counter;
	int		exit_counter;
	int		player_counter;
	int		ones_counter;
	int		zeros_counter;
}	so_long_var_t;


