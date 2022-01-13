/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:15:32 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/13 19:50:35 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static size_t	get_grid_size(t_tet **tets)
{
	size_t	count;
	size_t	grid_size;

	count = 0;
	while (tets[count])
		count++;
	grid_size = 2;
	while (grid_size * grid_size < count * 4)
		grid_size++;
	return (grid_size);
}

/*
 * solve() starts the backtracking recursion with the minimum possible
 * grid_size that can hold n * 4 tetrimino blocks (n = amount of tetriminos)
 */

void	solve(t_tet **tets)
{
	t_grid	grid;
	size_t	i;

	i = 0;
	while (i < 16)
		grid.grid[i++] = 0xffff;
	grid.grid_size = get_grid_size(tets);
	// TODO: zero grid_size * grid_size area in grid here
	while (1)
	{
		try_solution(&grid, grid.grid_size, tets, 0);
		grid.grid_size++;
	}
}
