/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slistle <slistle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:26:21 by slistle           #+#    #+#             */
/*   Updated: 2023/06/19 22:10:21 by slistle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int destroy_window(so_long_var_t *s)
{	
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}

void	memory(so_long_var_t *s, char *argv)
{
	int		j;
	int		fd;

	fd = open(argv, O_RDONLY);
	s->lines = 0;
	while (get_next_line(fd))
		s->lines++;
	close(fd);
	if(s->lines < 3)
	{
		printf("The map is too small");
		exit(0);
	}	
	s->map = malloc((s->lines + 1) * sizeof(char *));
	fd = open(argv, O_RDONLY);
	j = 0;
	while(j < s->lines)
	{
		s->map[j] = get_next_line(fd);
		j++;
	}
	s->map[j] = 0;
	s->map_x = ft_strlen(s->map[0]) - 1;
	close(fd);
}

void put_val_to_zero(so_long_var_t *s)
{
	s->moves_counter = 0;
	s->collectibles_counter = 0;
	s->player_counter = 0;
	s->exit_counter = 0;
}

void not_enough_case(so_long_var_t *s)
{
	if (s->collectibles_counter < 1)
	{
		printf("Nothing to clean here");
		destroy_window(s);
	}
	if (s->player_counter == 0)
	{
		printf("Who's gonna clean all this up??");
		destroy_window(s);
	}
	if (s->exit_counter == 0)
	{
		printf("There is no bucket in here");
		destroy_window(s);
	}
}

void one_case(so_long_var_t *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img_wall, s->x * 50, s->y * 50);
	
}

void zero_case(so_long_var_t *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img_ground, s->x * 50, s->y * 50);
}

void exit_case(so_long_var_t *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img_exit, s->x * 50, s->y * 50);
	s->exit_counter++;
	if (s->exit_counter > 1)
	{
		printf("Multiple exits detected.");
		destroy_window(s);
	}
}

void player_case(so_long_var_t *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->x * 50, s->y * 50);
	s->player_x = s->x;
	s->player_y = s->y;
	s->player_counter++;
	if (s->player_counter > 1)
	{
		printf("Muptiple players detected.");
		destroy_window(s);
	}
}

void collectibles_case(so_long_var_t *s)
{
	mlx_put_image_to_window(s->mlx, s->win, s->img_coin, s->x * 50, s->y * 50);
	s->collectibles_counter++;
	// printf("collectibles_counter  = %d\n", s->collectibles_counter);
}

void map_cases(so_long_var_t *s)
{
	if (s->map[s->y][s->x] == '1')
		one_case(s);
	else if (s->map[s->y][s->x] == '0')
		zero_case(s);
	else if (s->map[s->y][s->x] == 'E')
		exit_case(s);
	else if (s->map[s->y][s->x] == 'C')	
		collectibles_case(s);
	else if (s->map[s->y][s->x] == 'P')	
		player_case(s);
	else if (s->map[s->y][s->x] != '\n')
	{
		printf("x and y = %d\n", s->map[s->y][s->x]);
		printf("Strange elements detected. Abort.\n");
		destroy_window(s);
	}
}

void wall_check(so_long_var_t *s, int len)
{
	int	i;

	i = 0;
	while(s->map[0][i] != '\n')
	{
		if(s->map[0][i] != '1' || s->map[s->lines - 1][i] != '1')
		{
			printf("The wall is not the wall.");
			destroy_window(s);
		}
		i++;
	}
	i = 0;
	printf("len = [%d]\n", s->map[i][len - 2]);
	while (i < s->lines)
	{
		if (s->map[i][0] != '1' || s->map[i][len - 2] != '1')
		{
			printf("The wall is not the wall.");
			destroy_window(s);
		}
		i++;
	}
}

void map_check(so_long_var_t *s)
{
	int i;
	int len;
	int	len_max;

	i = 1;
	len_max = ft_strlen(s->map[0]);
	printf("len_max = [%d]\n", s->map[i][len_max]);
	while(i < s->lines)
	{
		len = ft_strlen(s->map[i]);
		if (len != len_max)
		{
			printf("not a rectangular map.");
			destroy_window(s);
		}
		i++;
	}
	wall_check(s, len_max);
	i = len + len_max + i;
}


void print_map(so_long_var_t *s)
{
	int	a;
	int	b;

	s->y = 0;
	s->img_wall = mlx_xpm_file_to_image(s->mlx, "map/1_wall.xpm", &a, &b);
	s->img_ground = mlx_xpm_file_to_image(s->mlx, "map/0_empty_space.xpm", &a, &b);
	s->img_player = mlx_xpm_file_to_image(s->mlx, "map/P_player.xpm", &a, &b);
	s->img_coin = mlx_xpm_file_to_image(s->mlx, "map/C_collectibles.xpm", &a, &b);
	s->img_exit = mlx_xpm_file_to_image(s->mlx, "map/E_exit.xpm", &a, &b);
	while(s->map[s->y] != 0)
	{
		s->x = 0;
		while(s->map[s->y][s->x] != 0)
		{
			// printf("%c", s->map[s->y][s->x]);
			map_cases(s);
			s->x++;
		}
		s->y++;
	}
}

void end_game(so_long_var_t *s)
{
	if (s->collectibles_counter == 0)
	{
		printf("Good job!");
		destroy_window(s);
	}
	else
	{
		printf("The floor is still dirty");
		mlx_put_image_to_window(s->mlx, s->win, s->img_exit, s->player_x * 50, s->player_y * 50);	
	}
}

void key_esc(so_long_var_t *s)
{
	mlx_destroy_window(s->mlx, s->win);
	exit(0);
}

void key_W(so_long_var_t *s)
{
	if (s->map[s->player_y][s->player_x] == 'C')
	{
		printf("collectibles_counter  = %d", s->collectibles_counter);
		s->map[s->player_y][s->player_x] = '0';
		printf("collectibles = %d", s->collectibles_counter);
		s->collectibles_counter--;
	}
	if (s->map[s->player_y][s->player_x] == 'E')
	{
		end_game(s);
		s->player_y--;
		s->moves_counter++;
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
	else
	{
		mlx_put_image_to_window(s->mlx, s->win, s->img_ground, s->player_x * 50, s->player_y * 50);	
		s->player_y--;
		s->moves_counter++;
		printf("\ncounter= %d\n", s->moves_counter);
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
}

void key_A(so_long_var_t *s)
{
	if (s->map[s->player_y][s->player_x] == 'C')
	{
		printf("collectibles_counter  = %d", s->collectibles_counter);
		s->map[s->player_y][s->player_x] = '0';
		printf("collectibles = %d", s->collectibles_counter);
		s->collectibles_counter--;
	}
	if (s->map[s->player_y][s->player_x] == 'E')
	{
		end_game(s);
		s->player_x--;
		s->moves_counter++;
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
	else
	{
		mlx_put_image_to_window(s->mlx, s->win, s->img_ground, s->player_x * 50, s->player_y * 50);
		s->player_x--;
		s->moves_counter++;
		printf("\ncounter= %d\n", s->moves_counter);
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
}

void key_S(so_long_var_t *s)
{
		if (s->map[s->player_y][s->player_x] == 'C')
	{
		printf("collectibles_counter  = %d", s->collectibles_counter);
		s->map[s->player_y][s->player_x] = '0';
		printf("collectibles = %d", s->collectibles_counter);
		s->collectibles_counter--;
	}
	if (s->map[s->player_y][s->player_x] == 'E')
	{
		end_game(s);
		s->player_y++;
		s->moves_counter++;
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
	else
	{	
		mlx_put_image_to_window(s->mlx, s->win, s->img_ground, s->player_x * 50, s->player_y * 50);
		s->player_y++;
		s->moves_counter++;
		printf("\ncounter= %d\n", s->moves_counter);
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
}

void key_D(so_long_var_t *s)
{
	if (s->map[s->player_y][s->player_x] == 'C')
	{
		printf("collectibles_counter  = %d", s->collectibles_counter);
		s->map[s->player_y][s->player_x] = '0';
		printf("collectibles = %d", s->collectibles_counter);
		s->collectibles_counter--;
	}
	if (s->map[s->player_y][s->player_x] == 'E')
	{
		end_game(s);
		s->player_x++;
		s->moves_counter++;
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
	else
	{
		mlx_put_image_to_window(s->mlx, s->win, s->img_ground, s->player_x * 50, s->player_y * 50);
		s->player_x++;
		s->moves_counter++;
		printf("\ncounter= %d\n", s->moves_counter);
		mlx_put_image_to_window(s->mlx, s->win, s->img_player, s->player_x * 50, s->player_y * 50);
	}
}

int	key_hook(int keycode, so_long_var_t *s)
{
	s->x = s->player_x;
	s->y = s->player_y;
	// printf("player_x = %d player_y = %d\n", s->player_x, s->player_y);
	// printf("x and y = %c\n", s->map[s->player_y][s->player_x]);

	if(keycode == 65307) // code for esc
		key_esc(s);
	else if ((s->map[s->y-1][s->x] != '1' ) && keycode == 1731) // code for w
		key_W(s);
	else if (s->map[s->y][s->x-1] != '1' && keycode == 1734) // code for a
		key_A(s);
	else if (s->map[s->y+1][s->x] != '1' && keycode == 1753) // code for s
		key_S(s);
	else if (s->map[s->y][s->x+1] != '1' && keycode == 1751) // code for d
		key_D(s);
	return (0);
}

int main(int argc, char **argv)
{
	so_long_var_t s;
	
	if (argc != 2)
		return (0);
	s.mlx = mlx_init();
	memory(&s, argv[1]);

	s.win = mlx_new_window(s.mlx, s.map_x * 50, s.lines * 50, "so_long");
	put_val_to_zero(&s);
	map_check(&s);
	print_map(&s);
	mlx_hook(s.win, 2, 1L<<0, key_hook, &s);
	mlx_hook(s.win, 17, 1L << 2, destroy_window, &s); //close by clicking X
	mlx_loop(s.mlx);
}



/*
че надо: 
1) cчетчик движений +
2) менять разрешение окна
3) закрывать на крестик +
4) проверять на наличие лишних элементов +
5) карта окружена стенами? +
6) вылетать с ошибкой
7) проверять на отсутствие важных элементов на карте, типа нет чего то +
8) проверять чтобы был один игрок и один выход +
9) больше трех строк в карте +
*/ 
