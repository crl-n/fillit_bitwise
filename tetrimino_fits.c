/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_fits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:29:15 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/10 19:29:50 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	update_grid_placement(t_tet *tet, size_t k, size_t l)
{
	tet->grid_placement[0] = k;
	tet->grid_placement[1] = l + tet->left_offset;
}

int	tetrimino_fits(t_tet *tet, t_grid *grid, size_t k, size_t l)
{
	size_t		i;
	u_int16_t	row;
	u_int16_t	nb = 0b1111000000000000;

	i = 0;
	while (i < 4)
	{
		row = ((tet->bits & nb) << (4 * i)) >> l;
		if (row)
			if (row & grid->grid[i + k])
			{
				while (i > 0)
				{
					i--;
					nb = nb << 4;
					row = ((tet->bits & nb) << (4 * i)) >> l;
					grid->grid[i + k] = grid->grid[i + k] ^ row;
				}
				return (0);
			}
		grid->grid[i + k] = grid->grid[i + k] | row;
		nb = nb >> 4;
		i++;
	}
	update_grid_placement(tet, k, l);
	return (1);
}
