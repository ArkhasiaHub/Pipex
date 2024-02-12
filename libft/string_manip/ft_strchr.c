/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:12:39 by sbriche           #+#    #+#             */
/*   Updated: 2023/11/15 16:07:54 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	if (s[0] == (unsigned char)c)
		return ((char *)s);
	while (*s != '\0')
	{
		s++;
		if (*s == (unsigned char)c)
			return ((char *)s);
	}
	return (0);
}