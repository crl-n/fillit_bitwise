#include <stdio.h>
#include "fillit.h"

void	shift_tet(u_int16_t *tet)
{
	u_int16_t	top_row = 0b1111000000000000;
	u_int16_t	left_col = 0b1000100010001000;
	while (!(top_row & *tet))
		*tet = *tet << 4;
	while (!(left_col & *tet))
		*tet = *tet << 1;
}

int	get_bit_tet(char *tet)
{
	int i;
	int	bitwise_tet = 0b0000000000000000;
	int	bitwise_nb_thing = 0b1000000000000000;

	i = 0;
	while (i < 20)
	{
		if (tet[i] != '\n')
		{
			if (tet[i] == '#')
			{
				//printf("is this infinitely looping or sth");
				bitwise_tet = bitwise_tet | bitwise_nb_thing;
			}
			bitwise_nb_thing = bitwise_nb_thing >> 1;
		}
		i++;

	}
	return (bitwise_tet);
}

void	fake_map(size_t grid_size, u_int16_t **fake_map)
{
	size_t		i;
	size_t		j;
	u_int16_t	bitwise_nb_thing = 0b1000000000000000;

	i = 0;
	while (i < 16)
	{
		*fake_map[i] = 0xffff;
		if (i < grid_size)
		{
			j = 0;
			while (j < grid_size)
			{
				*fake_map[i] = *fake_map[i] ^ bitwise_nb_thing;
				bitwise_nb_thing = bitwise_nb_thing >> 1;
				j++;
			}
		}
		i++;
	}
}

size_t	tet_fits(u_int16_t *map, size_t k, u_int16_t tet)
{
	size_t		i;
	u_int16_t	row;
	u_int16_t	nb = 0b1111000000000000;

	i = 0;
	while (i < 4)
	{
		row = ((tet & nb) << (4 * i)) >> k;
		printf("row is now: %x\n", row);
		if (row)
			if (row & map[i])
			{
				// remove
				while (i > 0)
				{
					i--;
					map[i] = map[i] ^ row;
				}
				return (0);
			}
				
		map[i] = map[i] | row;
		nb = nb >> 4;
		i++;
	}
	return (1);
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

/*int		is_valid(t_tet *tet)
{
	size_t	i;
	size_t nb_valid_tets = 30;
	u_int16_t	valid_tets[30];

	i = 0;
	while (i < nb_valid_tets)
	{
		if (tet->bits == valid_tets[i])
			return (1);
		i++;
	}
	return (0);
}

void	validate_tetrimino_bit (char *buff, ssize_t i, t_tet *tet)
{
	u_int16_t	bit_tet;

	bit_tet = get_bit_tet(buff[i]);
	shift_tet(&bit_tet);
	if (!is_valid(tet))
		invalid_input();
	tet->bits = bit_tet;
}*/

int	test(void)
{
	char		tetrimino1[21] = "...#\n...#\n...#\n...#\n";
	char		tetrimino3[21] = "....\n....\n..##\n.##.\n";
	u_int16_t	bit_tet1;
	u_int16_t	bit_tet2;
	u_int16_t	map[16];

	bit_tet1 = get_bit_tet(tetrimino3);
	bit_tet2 = get_bit_tet(tetrimino1);
	shift_tet(&bit_tet1);
	shift_tet(&bit_tet2);

	size_t		i;
	size_t		j;
	size_t		k;
	u_int16_t	bitwise_nb_thing;
	size_t grid_size = 4;

	i = 0;
	while (i < 16)
	{
		map[i] = 0xffff;
		if (i < grid_size)
		{
			j = 0;
			bitwise_nb_thing = 0b1000000000000000;
			while (j < grid_size)
			{
				map[i] = map[i] ^ bitwise_nb_thing;
				bitwise_nb_thing = bitwise_nb_thing >> 1;
				j++;
			}
		}
		i++;
	}

	printf("so the bitwised tetrimino is: %x\n", bit_tet1);
	print_map(map, grid_size);

	//try for every spot in first row
	k = 0;
	while (k < 16)
	{
		if (tet_fits(map, k, bit_tet1))
		{
			printf("first tet fits\n");
			break ;
		}
		k++;
	}
	
	print_map(map, grid_size);

	k = 0;
	while (k < 16)
	{
		if (tet_fits(map, k, bit_tet2))
		{
			printf("second tet fits\n");
			break ;
		}
		k++;
	}

	print_map(map, grid_size);
	return (0);
}
/*
tetrimino1
ok so we want it to look like this
0011011000000000
3600

tetrimino2
6 12 0 0
so 6c00 in hex
*/


/*

steps:

- validating tetriminos:
shift them the most up and left you can then compare against list of acceptable tets

- create map: 16 rows of 16 bits
set grid size: if its 5 for ex:
for each row, leave the first 5 off and set the remaining to 1s

- check if a tetrimino fits
for each of the 4 rows of the tet (unless its empty wihch u check with the & also)
you need to isolate the row right, so
esim tet & 1111000000000000 for the first row, etc
then you... check with this nb if theres a colision so here:
take first row of map : first_row_map & first_row_tet. if the result is not zero there's a collision

- place a tet

- remove a tet

- check all of the grids spots

*/