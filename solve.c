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

void	print_map(u_int16_t *map, size_t grid_size)
{
	size_t		i;

	printf("the map\n");
	i = 0;
	while (i < grid_size)
	{
		printf("%x\n", map[i]);
		i++;
	}
}

void	set_up_grid(t_grid	*grid_ptr, t_tet **tets)
{
	size_t	i;
	size_t	j;
	u_int16_t	bitwise_nb;
	t_grid	grid;

	grid = *grid_ptr;
	grid.grid_size = get_grid_size(tets);
	i = 0;
	while (i < 16)
	{
		grid.grid[i] = 0xffff;
		if (i < grid.grid_size)
		{
			j = 0;
			bitwise_nb = 0b1000000000000000;
			while (j < grid.grid_size)
			{
				grid.grid[i] = grid.grid[i] ^ bitwise_nb;
				bitwise_nb = bitwise_nb >> 1;
				j++;
			}
		}
		i++;
	}
}

/*
 * solve() starts the backtracking recursion with the minimum possible
 * grid_size that can hold n * 4 tetrimino blocks (n = amount of tetriminos)
 */

void	solve(t_tet **tets)
{
	t_grid	grid;
	size_t	i;
	size_t	j;
	u_int16_t	bitwise_nb;

	grid.grid_size = get_grid_size(tets);
	printf("grid size %zu\n", grid.grid_size);
	i = 0;
	while (i < 16)
	{
		grid.grid[i] = 0xffff;
		if (i < grid.grid_size)
		{
			j = 0;
			bitwise_nb = 0b1000000000000000;
			while (j < grid.grid_size)
			{
				grid.grid[i] = grid.grid[i] ^ bitwise_nb;
				bitwise_nb = bitwise_nb >> 1;
				j++;
			}
		}
		i++;
	}
	//set_up_grid(&grid, tets);
		
	//print_map(grid.grid, grid.grid_size);
	while (grid.grid_size < 14)
	{
		try_solution(&grid, grid.grid_size, tets, 0);
		grid.grid_size++;
	}
}
