/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:35:24 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/29 12:12:11 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/includes/ft_printf.h"

static char	*check_exception(char *path, char *cmd_name, int *i);
static char	*checking_acces(char *cmd, char *cmd_name, int *i);
static int	testing_path(char *cmd_name);

char	*find_path(t_commands *c, char *cmd_name, char **paths)
{
	char	*path;
	char	*cmd_tmp;
	int		i;

	path = NULL;
	cmd_tmp = check_exception(path, cmd_name, &i);
	if (i == -1)
		return (free_paths(paths), free_all(c), NULL);
	if (i == 1)
		return (cmd_tmp);
	while (paths[i])
	{
		cmd_tmp = ft_strjoin(paths[i], cmd_name);
		if (!cmd_tmp)
			return (free_paths(paths), free_all(c), NULL);
		if (access(cmd_tmp, F_OK | X_OK) != -1)
			return (cmd_tmp);
		free(cmd_tmp);
		cmd_tmp = NULL;
		i++;
	}
	ft_printf("%s : command not found\n", cmd_name);
	return (path);
}

static char	*check_exception(char *path, char *cmd_name, int *i)
{
	char	*cmd;

	cmd = NULL;
	path = NULL;
	*i = 0;
	if (cmd_name == NULL)
	{
		*i = 1;
		cmd = ft_strdup("");
		if (cmd == NULL)
			*i = -1;
		return (cmd);
	}
	if (testing_path(cmd_name) == 0)
		cmd = checking_acces(cmd, cmd_name, i);
	if (*i == 1)
		return (cmd);
	if (access(cmd_name, F_OK) == 0)
	{
		cmd = ft_strdup(cmd_name);
		if (cmd == NULL)
			*i = -1;
		*i = 1;
	}
	return (cmd);
}

static char	*checking_acces(char *cmd, char *cmd_name, int *i)
{
	*i = 1;
	if (access(cmd_name, F_OK) == 0)
	{
		if (access(cmd_name, X_OK) == 0)
			cmd = ft_strdup(cmd_name);
		else
		{
			cmd = ft_strdup("");
			if (cmd == NULL)
				*i = -1;
			perror(cmd_name);
			return (cmd);
		}
		if (cmd == NULL)
			*i = -1;
	}
	else
		perror(cmd_name);
	return (cmd);
}

static int	testing_path(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "./", 2) == 0)
		return (0);
	if (ft_strncmp(cmd_name, "/", 1) == 0)
		return (0);
	return (1);
}
