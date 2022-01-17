/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:54:33 by cnysten           #+#    #+#             */
/*   Updated: 2022/01/13 17:07:09 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "fcntl.h"

int	main(int argc, char **argv)
{
	t_tet	*tets[27];
	int		fd;

	if (argc != 2)
	{
		ft_putstr(USAGE);
		return (1);
	}
	ft_bzero(tets, sizeof(t_tet *) * 27);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error(tets);
	get_tetriminos(fd, tets);
	close(fd);
	get_dimensions(tets);
	get_prevs(tets);
	solve(tets);
	free_tetriminos(tets);
	return (0);
}
