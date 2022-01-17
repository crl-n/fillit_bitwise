/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:42:26 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/06 14:46:48 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

void	place_tet(char **solution, t_tet *tet)
{
	size_t	i;
	size_t	k;
	size_t	l;
	size_t	row;
	size_t	col;

	i = 0;
	k = tet->grid_placement[0];
	l = tet->grid_placement[1];
	while (i < 7)
	{
		row = k + tet->coords[i];
		col = (size_t)((int) l + tet->coords[i + 1]);
		solution[row][col] = tet->symbol;
		i += 2;
	}
}

/*
 * display_solution() is used to display the solution when the correct
 * solution has been found.
 */

void	display_solution(t_grid *grid, t_tet **tets)
{
	size_t	i;
	(void)grid;
	(void)tets;

	char	**solution;

	//printf("grid size %zu\n", grid->grid_size);
	solution = (char **)malloc(sizeof(char *) * grid->grid_size);
	//if (!solution)
	i = 0;
	while (i < grid->grid_size)
	{
		solution[i] = (char *)malloc(sizeof(char *) * (grid->grid_size + 1));
		ft_memset((void *)solution[i], '.', grid->grid_size);
		solution[i][grid->grid_size] = '\0';
		//if (!solution[i])
		i++;
	}

	i = 0;
	while (tets[i])
	{
		place_tet(solution, tets[i]);
		i++;
	}

	i = 0;
	while (i < grid->grid_size)
	{
		ft_putstr(solution[i]);
		ft_putchar('\n');
		i++;
	}
}
