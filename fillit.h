/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:08:49 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/13 20:13:03 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
//delete
#include <stdio.h>

/* Typedef for 16 bit unsigned integer */
typedef unsigned short t_uint16;

/* Tetrimino struct */
typedef struct s_tet
{
	char			symbol;
	t_uint16		bits;
	int				coords[8];
	size_t			width;
	size_t			height;
	size_t			left_offset;
	struct s_tet	*prev;
	size_t			grid_placement[2];
}					t_tet;

/* Grid struct */
typedef struct s_grid
{
	size_t	grid_size;
	t_uint16	grid[16];
}				t_grid;

/* Usage message */
# define USAGE "usage: ./fillit input_file\n"

/* Bitwise masks for each row of the bitwise representations of tetriminos */
# define ROW_1 0xf000;
# define ROW_2 0x0f00;
# define ROW_3 0x00f0;
# define ROW_4 0x000f;

/* Prototypes */
void	validate_tetrimino(t_tet *tet, t_tet **tets);
void	validate_tet_map(char *buff, ssize_t i, t_tet *tet, t_tet **tets);
void	free_tetriminos(t_tet **tets);
void	solve(t_tet **tets);
void	display_solution(t_grid *grid, t_tet **tets);
void	try_solution(t_grid *grid, size_t grid_size, t_tet **tets, size_t i);
int		tetrimino_fits(t_tet *tet, t_grid *grid, size_t k, size_t l);
void	get_prevs(t_tet **tets);
void	get_dimensions(t_tet **tets);
void	free_tetriminos(t_tet **tets);
void	handle_error(t_tet **tets);
void	get_prevs(t_tet **tets);
void	get_dimensions(t_tet **tets);
void	get_tetriminos(int fd, t_tet **tets);

#endif
