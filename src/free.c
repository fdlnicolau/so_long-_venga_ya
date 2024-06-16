/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:37:38 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/26 04:37:38 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void free_game(t_game *game) 
{
	if (game->map) 
	{
		free_map(game);
	}
	ft_clean_image(game);
	if(game->mlx)
	{
		mlx_terminate(game->mlx);
		free(game->mlx);
		exit(write(1, "\n[END_OF_PROGRAM]\n\n", 20));
	}
}

void ft_clean_image(t_game *game)
{
if (game->floor_img)
    {
        mlx_delete_image(game->mlx, game->floor_img);
        game->floor_img = NULL;
    }
    if (game->exit_img)
    {
        mlx_delete_image(game->mlx, game->exit_img);
        game->exit_img = NULL;
    }
    if (game->player_img)
    {
        mlx_delete_image(game->mlx, game->player_img);
        game->player_img = NULL;
    }
    if (game->wall_img)
    {
        mlx_delete_image(game->mlx, game->wall_img);
        game->wall_img = NULL;
    }
    if (game->collect_img)
    {
        mlx_delete_image(game->mlx, game->collect_img);
        game->collect_img = NULL;
    }
    if (game->str)
    {
        mlx_delete_image(game->mlx, game->str);
        game->str = NULL;
    }
}

void close_window(t_game *game)
{
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	exit(0);
}
void free_map(t_game *game)
{
	int i;

	i = 0;
	while (i < game->hgt)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void ft_exit_free(int nb_error, t_game *game)
{
	if (nb_error == EXTENSION_NO_BER)
		exit(write(1, "\n[ERROR]La extencion no es \".ber\".\n\n", 37));
	if (nb_error == END_OF_PROGRAM)
	{
		while (--game->hgt)
			free(game->map[game->hgt]);
		free(game->map[game->hgt]);
		free(game->map);
		ft_clean_image(game);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		exit(write(1, "\n[END_OF_PROGRAM]\n\n", 20));
	}
	if (nb_error == MAP_NOT_CORRECT)
		exit(write(1, "\n[ERROR]MAP_NOT_CORRECT.\n\n", 27));
}
void free_visit_matrix(int **visit, int rows)
{
    if (visit == NULL)
        return;

    for (int i = 0; i < rows; ++i)
    {
        if (visit[i] != NULL)
        {
            free(visit[i]);
            visit[i] = NULL;  // Opcional: asignar NULL después de liberar la memoria por precaución
        }
    }

    free(visit);
}
