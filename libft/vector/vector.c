/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:23:39 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/16 13:24:27 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

int	vector_init(t_vector **vec, size_t elemsize, size_t initial_capacity)
{
	*vec = (t_vector *) malloc (sizeof(t_vector));
	if (!(*vec))
		return (0);
	(*vec)->array = (void *) malloc (elemsize * initial_capacity);
	if (!(*vec)->array)
		return (free(*vec), 0);
	(*vec)->elemsize = elemsize;
	(*vec)->capacity = initial_capacity;
	(*vec)->allocated = 1;
	return (1);
}

void	*vector_get_at(const t_vector *vec, size_t index)
{
	if (index >= vec->capacity)
		return (NULL);
	return (&(vec->array)[index]);
}

int	vector_resize(t_vector **vec, size_t new_capacity)
{
	(*vec)->array = (void *) malloc ((*vec)->elemsize * new_capacity);
	if (!(*vec)->array)
	{
		return (free(*vec), 0);
	}
	(*vec)->capacity = new_capacity;
	return (1);
}

void	free_vector(t_vector *vec)
{
	free(vec->array);
	free(vec);
	vec = NULL;
}
