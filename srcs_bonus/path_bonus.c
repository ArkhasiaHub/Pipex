/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:37:00 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/29 10:42:21 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	free_path(t_commands *c, char **path, char *p, int size);
static char	**harcode_path(void);

int	find_path_env(t_commands *c, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		free_all(c);
	return (i);
}

char	**split_path(t_commands *c, char **env, int i)
{
	char	*p;
	char	**path;
	int		size;

	if (!env[i])
		return (harcode_path());
	p = ft_strchr(env[i], '/');
	path = ft_split(p, ':');
	if (!path)
		free_all(c);
	size = 0;
	while (path[size])
		size++;
	i = 0;
	while (path[i])
	{
		p = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			free_path(c, path, p, size);
		free(p);
		i++;
	}
	return (path);
}

static void	free_path(t_commands *c, char **path, char *p, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (path[i])
			free(path[i]);
		i++;
	}
	free(p);
	free(path);
	free_all(c);
}

static char	**harcode_path(void)
{
	char	**path;
	ssize_t	c;

	c = write(1, "Path not found: Defaulting to bash hardcode default.\n", 54);
	if (c == -1)
		return (NULL);
	path = ft_split("/usr/local/sbin/:/usr/local/bin/:" \
	"/usr/sbin/:/usr/bin/:/sbin/:/bin/", ':');
	return (path);
}
