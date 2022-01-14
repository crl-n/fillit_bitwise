/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_solution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:32:12 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 19:32:56 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * remove_tetrimino() resets the characters in the grid to '.'.
 */

void	remove_tetrimino(t_tet *tet, t_grid *grid, size_t k, size_t l)
{
	size_t		i;
	u_int16_t	row;
	u_int16_t	nb = 0b1111000000000000;

	i = 0;
	while (i < 4)
	{
		row = ((tet->bits & nb) << (4 * i)) >> l;
		if (row)
		{
			grid->grid[i + k] = grid->grid[i + k] ^ row;
		}
		i++;
	}
}

/*
 * If tetrimino is NULL, all tetriminos have been placed onto the map.
 * This means the correct solution has been found. In that case, the correct
 * solution is displayed and heap allocated memory is freed.
 */

void	check_if_solved(t_tet *tet, t_tet **tets, t_grid *grid)
{
	//(void)grid;
	if (!tet)
	{
		display_solution(grid, tets);
		free_tetriminos(tets);
		exit(0);
	}
}

void	set_start(size_t *k, size_t *l, t_tet *tet)
{
	*k = 0;
	//*l = 0;
	*l = 0 + tet->left_offset;
	if (tet->prev)
	{
		*k = tet->prev->grid_placement[0];
		*l = tet->prev->grid_placement[1];
	}
}

void	try_solution(t_grid *grid, size_t grid_size, t_tet **tets, size_t i)
{
	size_t	k;
	size_t	l;
	printf("hey, i is %zu\n", i);
	check_if_solved(tets[i], tets, grid);
	set_start(&k, &l, tets[i]);
	while (k + tets[i]->height - 1 < grid_size)
	{
		while (l + tets[i]->width - 1 < grid_size)
		{
			if (tet_fits(tets[i], grid, k, l))
			{
				printf("hello, is is %zu and k is %zu and l is %zu\n", i, k, l);
				try_solution(grid, grid_size, tets, i + 1);
				remove_tetrimino(tets[i], grid, k, l);
			}
			l++;
		}
		k++;
		l = 0 + tets[i]->left_offset;
	}
}
