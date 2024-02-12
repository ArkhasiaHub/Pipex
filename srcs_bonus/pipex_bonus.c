/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:59:13 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/23 15:02:11 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	first_process(t_commands *c, char **env, int fd[2]);
static int	create_process(t_commands *c, int i, char **env, int fd[2]);
static int	last_process(t_commands *c, char **env);
static void	free_all_done(t_commands *c);

int	main(int argc, char **argv, char **env)
{
	t_commands	*c;
	int			i;
	int			fd[2];

	c = get_command(argc, argv, env);
	if (!c)
		return (1);
	i = -1;
	c->old_pipe = -1;
	init_pids(c);
	while (++i < c->size - 1)
	{
		if (pipe(fd) == -1)
			return (free_all(c), -1);
		if (i == 0)
			first_process(c, env, fd);
		else
			create_process(c, i, env, fd);
		c->old_pipe = fd[RD];
	}
	last_process(c, env);
	return (free_all_done(c), close(fd[RD]), 0);
}

static int	first_process(t_commands *c, char **env, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		free_all(c);
	if (pid == 0)
	{
		if (c->fd1 == -1)
		{
			close_fd(c->fd2, c->fd1, fd[RD], fd[WR]);
			return (free_all(c), 1);
		}
		close(c->fd2);
		dup2(c->fd1, STDIN_FILENO);
		close(c->fd1);
		close(fd[RD]);
		dup2(fd[WR], STDOUT_FILENO);
		close(fd[WR]);
		execve(c->cmd[0]->path, c->cmd[0]->args, env);
		free_all(c);
	}
	c->pids[0] = pid;
	close(fd[WR]);
	return (1);
}

static int	create_process(t_commands *c, int i, char **env, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		free_all(c);
	if (pid == 0)
	{
		if (c->old_pipe < 0)
		{
			close_fd(fd[RD], c->fd1, c->fd2, c->old_pipe);
			return (close(fd[WR]), free_all(c), 1);
		}
		close_fd(fd[RD], c->fd1, c->fd2, -1);
		dup2(c->old_pipe, STDIN_FILENO);
		close(c->old_pipe);
		dup2(fd[WR], STDOUT_FILENO);
		close(fd[WR]);
		execve(c->cmd[i]->path, c->cmd[i]->args, env);
		free_all(c);
	}
	c->pids[i] = pid;
	if (c->old_pipe >= 0)
		close(c->old_pipe);
	return (close(fd[WR]), 1);
}

static int	last_process(t_commands *c, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		free_all(c);
	if (pid == 0)
	{
		if (c->fd2 == -1 || c->old_pipe < 0)
		{
			close_fd(c->fd1, c->old_pipe, c->fd2, -1);
			return (free_all(c), 1);
		}
		close(c->fd1);
		dup2(c->old_pipe, STDIN_FILENO);
		close(c->old_pipe);
		dup2(c->fd2, STDOUT_FILENO);
		close(c->fd2);
		execve(c->cmd[c->size - 1]->path, c->cmd[c->size - 1]->args, env);
		free_all(c);
	}
	if (c->old_pipe >= 0)
		close(c->old_pipe);
	c->pids[c->size - 1] = pid;
	return (wait_all_pids(c), 1);
}

static void	free_all_done(t_commands *c)
{
	close(c->fd1);
	close(c->fd2);
	if (c->pids != NULL)
		free(c->pids);
	free_commands(c);
}
