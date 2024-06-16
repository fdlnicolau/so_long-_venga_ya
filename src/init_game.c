/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:49:29 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/10 20:02:12 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void game_control(t_game *game)
{
	game->wth = ft_strlen(game->map[0]);
	game->mlx = mlx_init(game->wth * S, game->hgt * S, "so_long", false);
	if(game->mlx == NULL)
			ft_error("mlx_init failed");
	load_image(game);
	mlx_image_to_window(game->mlx, game->player_img, game->player_ps[0] * S, game->player_ps[1] * S);
	mlx_key_hook(game->mlx, &init_key_hook, game);
	mlx_loop(game->mlx);
}

void load_image(t_game *game)
{
	load_png(game);
	texture_to_img(game);
	img_to_window(game);
}

void img_to_window(t_game *game)
{
    int	i;
    int	j;

    i = -1;
    while (++i <= game->hgt - 1)
    {
        j = -1;
        while (++j <= game->wth - 1) 
        {
            mlx_image_to_window(game->mlx, game->floor_img, j * S, i * S);
            if (game->map[i][j] == '1')
                mlx_image_to_window(game->mlx, game->wall_img, j * S, i * S);
            else if (game->map[i][j] == 'C' && game->collect_img != NULL)
                mlx_image_to_window(game->mlx, game->collect_img, j * S, i * S);
            else if (game->map[i][j] == 'P')
            {
                game->player_ps[1] = i;
                game->player_ps[0] = j;
            }
            else if (game->map[i][j] == 'E')
                mlx_image_to_window(game->mlx, game->exit_img, j * S, i * S);
        }
    }
}


void load_png(t_game *game)
{
	game->floor_tex = mlx_load_png("./sprites/floor.png");
	game->exit_tex = mlx_load_png("./sprites/exit.png");
	game->player_tex = mlx_load_png("./sprites/player.png");
	game->wall_tex = mlx_load_png("./sprites/wall.png");
	game->collect_tex = mlx_load_png("./sprites/collect.png");
	if(!game->floor_tex || !game->exit_tex || !game->player_tex || !game->wall_tex || !game->collect_tex)
		ft_error("Error loading texture");
}

void texture_to_img(t_game *game)
{
	game->floor_tex = mlx_load_png("./sprites/floor.png");
	game->exit_tex = mlx_load_png("./sprites/exit.png");
	game->player_tex = mlx_load_png("./sprites/player.png");
	game->wall_tex = mlx_load_png("./sprites/wall.png");
	game->collect_tex = mlx_load_png("./sprites/collect.png");

	if (!game->floor_tex || !game->exit_tex || !game->player_tex || !game->wall_tex || !game->collect_tex)
		ft_error("Error loading texture");

	game->floor_img = mlx_texture_to_image(game->mlx, game->floor_tex);
	game->exit_img = mlx_texture_to_image(game->mlx, game->exit_tex);
	game->player_img = mlx_texture_to_image(game->mlx, game->player_tex);
	game->wall_img = mlx_texture_to_image(game->mlx, game->wall_tex);
	game->collect_img = mlx_texture_to_image(game->mlx, game->collect_tex);
}

void game_init(t_game *game)
{
	game->map = NULL;
	game->players = 0;
	game->exit = 0;
	game->collectibles = 0;
	game->hgt = 0;
	game->wth = 0;
	game->window = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->floor_tex = NULL;
	game->wall_tex = NULL;
	game->collectible_tex = NULL;
	game->player_tex = NULL;
	game->exit_tex = NULL;
	game->collect_text = NULL;
	game->floor_img = NULL;
	game->exit_img = NULL;
	game->player_img = NULL;
	game->wall_img = NULL;
	game->collect_img = NULL;
	game->player_ps[0] = 0;
	game->player_ps[1] = 0;
	game->mlx = NULL;
	game->collect_tex = NULL;
	game->steps = 0;
	game->str = NULL;
	game->temp = NULL;
	game->player_exit = 0;
}