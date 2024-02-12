/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:52:13 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/19 16:54:49 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	check_infile(char *path);
static int	check_outfile(char *path);

t_commands	*check_file(int argc, char **argv)
{
	t_commands	*c;
	int			fd1;
	int			fd2;

	fd1 = check_infile(argv[1]);
	fd2 = check_outfile(argv[argc - 1]);
	c = create_command(argc);
	if (!c)
		exit(EXIT_FAILURE);
	c->fd1 = fd1;
	c->fd2 = fd2;
	return (c);
}

static int	check_infile(char *path)
{
	int	infile;

	infile = open(path, O_RDONLY);
	if (infile == -1)
		perror(path);
	return (infile);
}

static int	check_outfile(char *path)
{
	int	outfile;

	outfile = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (outfile == -1)
		perror(path);
	return (outfile);
}
