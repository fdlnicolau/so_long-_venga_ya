/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolau <lnicolau@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:40:29 by lnicolau          #+#    #+#             */
/*   Updated: 2024/05/20 15:40:29 by lnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int main(int argc, char **argv) 
{
	t_game  game;

	game_init(&game);
	if(argc == 2)
	{
		check_map(argv[1], &game);
		game_control(&game);
	}
	ft_exit_free(END_OF_PROGRAM, &game);
	return (EXIT_SUCCESS);
}

t_game *game_memory_init(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (*game == NULL)
		ft_error("Failed to allocate memory for the game");
	(*game)->map = NULL;
	return (*game);
}

void check_map(char *str, t_game *game)
{
	char *final;

	final = ft_strdup (str + ft_strlen(str) - 4);
	if (final == NULL)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if(ft_strncmp(final, ".ber", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		free(final);
		exit(EXIT_FAILURE);
	}
	read_map(game, str);
	free(final);
}
