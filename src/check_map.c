/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:04:14 by lnicolau          #+#    #+#             */
/*   Updated: 2024/06/10 20:02:01 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int map_size(int fd)
{
	char *line;
	int size;

	size = 0;
	while((line = get_next_line(fd)) != NULL)
	{
		size++;
		free(line);
	}
	return (size);
}

void read_map(t_game *game, char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error opening file");
		exit(EXIT_FAILURE);
	}
	game->hgt = map_size(fd);
	close(fd);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_error("Error opening file");
		exit(EXIT_FAILURE);
	}
	preparation_map(game);
	reading(fd, game);
	close(fd);
	parsing(game, str);
}

char *reading(int fd, t_game *game)
{
	char *line;
	int wth;
	int i;
	int j;

	i = 0;
	line = get_next_line(fd);
	if(line == NULL)
		ft_error("Empty file");
	while (line)
	{
		copy_line(game, line, i);
		j = 0;
		wth = ft_strlen(line);
		while (j < wth)
		{
			check_map_content(game, game->map[i][j], i, j);
			j++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = NULL;
	check_status(game);
	return NULL;
}

void check_status(t_game *game)
{
	if(!game->players)
		ft_error("Player not found");
	if(!game->exit)
		ft_error("Exit not found");
	if(game->collectibles == 0)
		ft_error("Collectibles not found");
}

void copy_line(t_game *game, char *line, int i)
{
    int len = strlen(line);
	int j = 0;

    game->map[i] = malloc(sizeof(char) * (len + 1));
    if (!game->map[i])
    {
        perror("Failed to allocate memory for game->map[i]");
        exit(EXIT_FAILURE);
    }
	if (line[j] != '\0' && line[j] != '\n' && line[j] != '\r')
    	strcpy(game->map[i], line);
	game->map[i][len] = '\0';
}

void check_map_content(t_game *game, char cell, int i, int j) 
{
if (cell == 'P')
	{
		if (game->players == 0)
		{
			game->player_x = j;
			game->player_y = i;
			game->players = 1;
		}
		else
		{
			ft_error("Multiple players found");
		}
	}
	else if (cell == 'C')
		game->collectibles += 1;
	else if (cell == 'E')
	{
		if (game->exit == 0)
			game->exit = 1;
		else
			ft_error("Multiple exits found");
	}
	else if (cell != '1' && cell != '0' && cell != '\n' && cell != '\r' && cell != '\0')
		ft_error("Unexpected cell character");
}


void preparation_map(t_game *game)
{
	game->map = malloc(sizeof(char *) * (game->hgt + 1));
	if (!game->map)
	{
		perror("Failed to allocate memory for map");
		exit(EXIT_FAILURE);
	}
	ft_memset(game->map, 0, sizeof(char *) * (game->hgt + 1));
}
