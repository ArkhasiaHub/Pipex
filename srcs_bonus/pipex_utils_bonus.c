/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:27:10 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/23 10:28:28 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_pids(t_commands *c)
{
	c->pids = ft_calloc(c->size, sizeof(pid_t));
	if (!c->pids)
		free_all(c);
}

void	free_all(t_commands *c)
{
	close(c->fd1);
	close(c->fd2);
	if (c->pids != NULL)
		free(c->pids);
	free_commands(c);
	exit(EXIT_FAILURE);
}

void	wait_all_pids(t_commands *c)
{
	int	i;

	i = 0;
	while (i < c->size)
	{
		waitpid(c->pids[i], NULL, 0);
		i++;
	}
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
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
