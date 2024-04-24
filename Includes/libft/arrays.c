/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:25:12 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:01:18 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_array(char c, char *params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		if (c == params[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_index(char c, char *params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		if (params[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
