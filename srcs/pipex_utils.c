/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:05:42 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/26 09:18:15 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(t_commands *c)
{
	close(c->fd1);
	close(c->fd2);
	if (c->pids != NULL)
		free(c->pids);
	free_commands(c);
	exit(EXIT_FAILURE);
}

void	free_all_done(t_commands *c)
{
	close(c->fd1);
	close(c->fd2);
	if (c->pids != NULL)
		free(c->pids);
	free_commands(c);
}

void	close_fd(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (fd4 >= 0)
		close(fd4);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
}
