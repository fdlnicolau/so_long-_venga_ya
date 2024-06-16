/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:39:56 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/14 12:43:46 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
void check_collectibles(t_game *game, int **visit)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < game->hgt)
	{
		j = 0;
		while(j < game->wth)
		{
			if (game->map[i][j] == 'C' && visit[i][j] == 1)
			{
				game->collectibles--;
			}
			j++;
		}
		i++;
	}
}
int **init_visit(int hgt, int wth)
{
	int i;
	int **visit;

	i = 0;
	visit = (int **)malloc(sizeof(int *) * hgt);
	if (visit == NULL)
		ft_error("error");
	while (i < hgt)
	{
		visit[i] = (int *)malloc(sizeof(int) * wth);
		if (visit[i] == NULL)
			ft_error("error");
		i++;
	}
	return (visit);
}

void check_path(t_game *game, int i, int j, int **visit)//flufli
{
	if (i < 0 || i >= game->hgt || j < 0 || j >= game->wth
		|| visit[i][j] || game->map[i][j] == '1')
		return;

	visit[i][j] = 1;
	if (game->map[i][j] == '1')
		return;

	if (game->map[i][j] == 'E')
	{
		game->exit = 1;
		return;
	}

	check_path(game, i - 1, j, visit);
	check_path(game, i + 1, j, visit);
	check_path(game, i, j - 1, visit);
	check_path(game, i, j + 1, visit);
}