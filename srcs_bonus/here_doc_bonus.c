/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:07:05 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/23 11:02:20 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../libft/includes/get_next_line.h"

static int	open_doc(void);

int	here_doc(char **argv)
{
	size_t	size[2];
	char	*tmp;
	int		fd;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		fd = open_doc();
		size[0] = ft_strlen(argv[2]);
		while (1)
		{
			tmp = get_next_line(1);
			if (!tmp)
				exit(EXIT_FAILURE);
			size[1] = ft_strlen(tmp);
			if (ft_strncmp(tmp, argv[2], size[0]) == 0 && \
				size[1] == size[0] + 1)
			{
				close(fd);
				return (free(tmp), 1);
			}
			write(fd, tmp, size[1]);
			free(tmp);
		}
	}
	return (-1);
}

static int	open_doc(void)
{
	int	fd;

	fd = open("/dev/shm/.h_docs", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
