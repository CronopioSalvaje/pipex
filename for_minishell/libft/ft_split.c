/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:35:41 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/23 10:17:16 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim(char *s, char c, int d)
{
	if (d <= 0)
		while (*s && *s != c)
			s++;
	if (d > 0)
		while (*s && *s == c)
			s++;
	return (s);
}

size_t	count_word(char const *s, char c)
{
	size_t	word;
	char	*str;

	str = (char *)s;
	if (!str)
		return (0);
	word = 0;
	while (*str)
	{
		str = trim(str, c, 1);
		if (*str)
			word++;
		str = trim(str, c, -1);
	}
	return (word);
}

size_t	get_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	size_t	index;
	int i;

	i = 0;
	index = 0;
	splitted = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!splitted || !s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] == c)
			s++;
		if (s[i] && s[i] != c)
		{
			splitted[index++] = ft_substr(&s[i], 0, get_len(&s[i], c));
			i += get_len(&s[i], c);
		}
	}
	splitted[index] = NULL;
	return (splitted);
}

char	**ft_split_key_val(char const *s, char c)
{
	char **splitted;
	size_t index;
	int i;

	i = 0;
	index = 0;
	splitted = (char **)malloc(3 * sizeof(char *));
	if (!splitted || !s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			splitted[index++] = ft_substr(&s[i], 0, get_len(&s[i], c));
			i += get_len(&s[i], c) + 1;
			splitted[index++] = ft_substr(&s[i], 0, ft_strlen(&s[i]));
			break ;
		}
	}
	splitted[index] = NULL;
	return (splitted);
}
