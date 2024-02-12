/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:59:22 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/23 10:31:58 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/includes/string_manip.h"
# include "../libft/includes/mem_manip.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_command
{
	char	*path;
	char	**args;
}	t_command;

typedef struct s_commands
{
	t_command	**cmd;
	pid_t		*pids;
	int			size;
	int			fd1;
	int			fd2;
	int			old_pipe;
}	t_commands;

typedef enum e_pipe
{
	RD,
	WR
}	t_pipe;

t_commands	*create_command(int argc);
t_commands	*get_command(int argc, char **argv, char **env);
int			get_command_name(t_commands *c, char **argv);
void		free_commands(t_commands *c);
int			find_path_env(char **env);
char		*find_path(t_commands *c, char *cmd_name, char **paths);
t_commands	*check_file(int argc, char **argv);
char		**split_path(t_commands *c, char **env, int i);
void		free_all(t_commands *c);
void		free_all(t_commands *c);
void		close_fd(int fd1, int fd2, int fd3, int fd4);
void		free_paths(char **paths);
void		free_all_done(t_commands *c);

#endif
