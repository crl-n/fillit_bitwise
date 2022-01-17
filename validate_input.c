/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:27:38 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/13 20:15:21 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	handle_block(size_t *block_count, t_tet *tet, int j, t_uint16 mask, t_tet **tets)
{
	static int		first_coord[2];

	(*block_count)++;
	if (*block_count > 4)
		handle_error(tets);
	if (*block_count == 1)
	{
		tet->coords[0] = 0;
		tet->coords[1] = 0;
		first_coord[0] = (int)j / 5;
		first_coord[1] = j % 5;
	}
	if (*block_count > 1)
	{
		tet->coords[(*block_count - 2) * 2 + 2] = (int)j / 5 - first_coord[0];
		tet->coords[(*block_count - 2) * 2 + 2 + 1] = j % 5 - first_coord[1];
	}
	tet->bits = tet->bits | mask;
}

void	shift_tet(t_tet *tet, t_tet **tets)
{
	u_int16_t	top_row = 0b1111000000000000;
	u_int16_t	left_col = 0b1000100010001000;
	if (tet->bits == 0x0000)
		handle_error(tets);
	while (!(top_row & tet->bits))
		tet->bits = tet->bits << 4;
	while (!(left_col & tet->bits))
		tet->bits = tet->bits << 1;
}

/*
 * validate_tetrimino() checks if a tetrimino is valid by comparing it to
 * a hard-coded list of the 19 valid tetriminos.
 *
 * Valid tetriminos are described in hex form. Each hex digit corresponds
 * to 4 bits in the bitmap. For instance, 0xf000 translates to:
 *
 * 		f	1111
 * 		0	0000
 * 		0	0000
 * 		0	0000
 */

void	validate_tetrimino(t_tet *tet, t_tet **tets)
{
	if (tet->bits == 0xf000
			|| tet->bits == 0x8888
			|| tet->bits == 0xcc00
			|| tet->bits == 0x88c0
			|| tet->bits == 0x2e00
			|| tet->bits == 0xc440
			|| tet->bits == 0xe800
			|| tet->bits == 0x44c0
			|| tet->bits == 0xe200
			|| tet->bits == 0xc880
			|| tet->bits ==  0x8e00
			|| tet->bits ==  0x6c00
			|| tet->bits ==  0x8c40
			|| tet->bits ==  0xc600
			|| tet->bits ==  0x4c80
			|| tet->bits ==  0x4e00
			|| tet->bits ==  0x4c40
			|| tet->bits ==  0xe400
			|| tet->bits ==  0x8c80)
		return ;
	handle_error(tets);
}

/*
 * The function validate_tet_map() checks if:
 * 		∙ Lines between tetriminos are empty
 * 		∙ Each line consists of valid characters
 * 		∙ Lines are of correct length
 *
 * validate_line() also calls handle_block() when a block is found.
 */

void	validate_tet_map(char *buff, ssize_t i, t_tet *tet, t_tet **tets)
{
	ssize_t			j;
	static size_t	block_count;
	t_uint16	mask;

	block_count = 0;
	if (buff[i + 4] != '\n' || buff[i + 9] != '\n' || buff[i + 14] != '\n' \
		|| buff[i + 19] != '\n' || buff[i + 20] != '\n')
		handle_error(tets);
	mask = 0x8000;
	j = 0;
	while (j < 21)
	{
		if (j == 4 || j == 9 || j == 14 || j == 19 || j == 20)
		{
			j++;
			continue ;
		}
		if (buff[j + i] != '#' && buff[j + i] != '.')
			handle_error(tets);
		if (buff[j + i] == '#')
			handle_block(&block_count, tet, j, mask, tets);
		j++;
		mask = mask >> 1;
	}
	shift_tet(tet, tets);
	validate_tetrimino(tet, tets);
}
