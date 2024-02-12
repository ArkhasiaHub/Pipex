/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:13:53 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/29 12:02:32 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/includes/ft_printf.h"

static int	quote_spliting(char **args);

t_commands	*create_command(int argc)
{
	t_commands	*c;
	int			i;

	c = ft_calloc(1, sizeof(t_commands));
	if (!c)
		return (NULL);
	c->size = argc - 3;
	c->cmd = ft_calloc(argc - 3, sizeof(t_command *));
	if (!c->cmd)
		return (free(c), NULL);
	i = -1;
	while (++i < argc - 3)
	{
		c->cmd[i] = ft_calloc(1, sizeof(t_command));
		if (!c->cmd[i])
			return (free_commands(c), NULL);
		c->cmd[i]->args = NULL;
		c->cmd[i]->path = NULL;
	}
	c->pids = NULL;
	return (c);
}

int	get_command_name(t_commands *c, char **argv)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (++i < c->size)
	{
		if (argv[++j][0] == '\0')
		{
			c->cmd[i]->args = ft_calloc(2, sizeof(char *));
			if (!c->cmd[i]->args)
				return (0);
			c->cmd[i]->args[0] = NULL;
			ft_printf("command not found : ''\n");
		}
		else
		{
			c->cmd[i]->args = ft_split(argv[j], ' ');
			if (!c->cmd[i]->args)
				return (0);
			if (!quote_spliting(c->cmd[i]->args))
				return (0);
		}
	}
	return (1);
}

void	free_commands(t_commands *c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < c->size)
	{
		if (!c->cmd[i])
			break ;
		if (c->cmd[i]->args)
		{
			j = 0;
			while (c->cmd[i]->args[j])
				free(c->cmd[i]->args[j++]);
			if (c->cmd[i]->args != NULL)
				free(c->cmd[i]->args);
		}
		if (c->cmd[i]->path != NULL)
			free(c->cmd[i]->path);
		free(c->cmd[i]);
	}
	free(c->cmd);
	c->cmd = NULL;
	free(c);
	c = NULL;
}

t_commands	*get_command(int argc, char **argv, char **env)
{
	t_commands	*c;
	char		**paths;
	int			i;

	if (argc != 5)
		return (ft_printf("Bad arguments\n"), NULL);
	c = check_file(argc, argv);
	paths = NULL;
	if (env[0] == NULL)
		write(2, "No env or PATH variable\n", 25);
	else
		paths = split_path(c, env, find_path_env(env));
	if (!get_command_name(c, argv))
		return (free_paths(paths), free_all(c), NULL);
	i = 0;
	while (i < c->size)
	{
		c->cmd[i]->path = find_path(c, c->cmd[i]->args[0], paths);
		i++;
	}
	return (free_paths(paths), c);
}

static int	quote_spliting(char **args)
{
	size_t	i[3];
	size_t	len;
	char	*tmp;

	i[0] = 0;
	while (args[i[0]])
	{
		len = ft_strlen(args[i[0]]);
		i[2] = len;
		i[1] = 0;
		if (args[i[0]][0] == 39)
			i[1] = 1;
		else if (args[i[0]][len - 1] == 39)
			i[2]--;
		tmp = ft_substr(args[i[0]], i[1], i[2]);
		if (tmp == NULL)
			return (0);
		free(args[i[0]]);
		args[i[0]] = tmp;
		i[0]++;
	}
	return (1);
}
