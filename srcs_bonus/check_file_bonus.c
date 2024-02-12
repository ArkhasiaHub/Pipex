/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:52:13 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/23 10:51:45 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	check_infile(char *path);
static int	check_outfile(char *path, int doc);
static void	close_fds(int fd1, int fd2);

t_commands	*check_file(int argc, char **argv)
{
	t_commands	*c;
	int			fd1;
	int			fd2;
	int			doc;

	doc = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		here_doc(argv);
		fd1 = check_infile("/dev/shm/.h_docs");
		doc = 1;
	}
	else
		fd1 = check_infile(argv[1]);
	fd2 = check_outfile(argv[argc - 1], doc);
	c = create_command(argc, doc);
	if (!c)
	{
		close_fds(fd1, fd2);
		exit(EXIT_FAILURE);
	}
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

static int	check_outfile(char *path, int doc)
{
	int	outfile;

	if (doc == 0)
		outfile = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		outfile = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (outfile == -1)
		perror(path);
	return (outfile);
}

static void	close_fds(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
