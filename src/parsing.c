/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:16:02 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/26 04:16:02 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int parsing(t_game *game, char *argv)
{
	size_t i;
	size_t j;
	int **visit;

	(void)argv;
	i = 0;
	j = 0;
	visit = NULL;
	//check_rect_map(game);
	check_components(game);
	check_walls(game);
	visit = start_check_path(game, i, j);
	check_collectibles(game, visit);
	return (0);
}

void check_walls(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;

	while (j < game->wth)
    {
        if (game->map[0][j] != '1')
            ft_error("Top wall check failed");
        j++;
    }

    j = 0;
    while (j < game->wth)
    {
        if (game->map[game->hgt - 1][j] != '1')
            ft_error("Bottom wall check failed");
        j++;
    }

	while( i < game->hgt)
	{
		if (game->map[i][0] != '1')
            ft_error("Left wall check failed");
		
		j = game->wth;
        if (game->map[i][j] != '1')
            ft_error("Right wall check failed");
		i++;
	}
}
void check_components(t_game *game)
{
	int i;
	int j;
	char valid_chars[] = "10CEP\r\n";


	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] != '\0' && ft_strchr(valid_chars, game->map[i][j]) == NULL)
				ft_error("invalid character in map");
			j++;
		}
		i++;
	}
	if (count_comp(game->map, 'P') != 1)
		ft_error("Ocurrió un error con el jugador");
	if(count_comp(game->map, 'E') != 1)
		ft_error("Ocurrió un error con la salida");
	if(count_comp(game->map, 'C') == 0)
		ft_error("Ocurrió un error con los colectables");
}

void check_rect_map(t_game *game)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_strlen(game->map[0]);
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
			j++;
		if (j != len)
			ft_error("Bad line length");
		i++;
	}
	if(i < 3)
		ft_error("Map too small");
	game->wth = len;
	game->hgt = i;
}

int **start_check_path(t_game *game, int i, int j)
{
	int **visit;
	visit = init_visit(game->hgt, game->wth);

	while(i < game->hgt)
	{
		j = 0;
		while(j < game->wth)
		{
			if (game->map[i][j] == 'P')
				check_path(game, i, j, visit);
			j++;
		}
		i++;
	}
	if (!game->exit)
		ft_error("Ocurrió un error");
		
	i = 0;
	while(i < game->hgt)
	{
		free(visit[i]);
		i++;
	}
	free(visit);
	return(visit);
}
