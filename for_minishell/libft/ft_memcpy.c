/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:50:42 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/23 10:17:19 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*temp;

	if ((dest == 0 && src == 0) && n != 0)
		return (0);
	temp = (char *)dest;
	while (n--)
		*temp++ = *(char *)src++;
	return (dest);
}
