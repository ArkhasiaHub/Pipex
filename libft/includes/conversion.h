/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbriche <sbriche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:18:19 by sbriche           #+#    #+#             */
/*   Updated: 2024/01/16 13:27:22 by sbriche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

# include <stdlib.h>
# include "./is_type.h"

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

#endif