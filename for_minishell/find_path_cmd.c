/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:32:26 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/27 06:18:08 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	joint_str_final_path(char *tmp, char **cmd_args, int len_path_total)
{
	ft_strlcat(tmp, "/", 2);
	ft_strlcat(tmp, cmd_args[0], len_path_total - ft_strlen(tmp));
}
/*
	/usr/local/sbin
	/usr/local/bin
	/usr/sbin
	/usr/bin
	/sbin
	/bin
	/usr/games
	/usr/local/games
	/snap/bin
	/snap/bin
*/
static char	*search_final_path(t_data *data, char **cmd_args)
{
	char	*path_final;
	char	*tmp;
	int		j;
	int		len_path_total;

	path_final = NULL;
	j = 0;
	while (data->paths[j] != NULL)
	{
		len_path_total = ft_strlen(data->paths[j]) + ft_strlen(cmd_args[0]) + 2;
		tmp = (char *)malloc(sizeof(char) * (len_path_total + 1));
		if (tmp == NULL)
			return (free_malloc_split(data->paths), NULL);
		ft_strlcpy(tmp, data->paths[j], len_path_total);
		joint_str_final_path(tmp, cmd_args, len_path_total);
		if (access(tmp, X_OK) == 0)
		{
			path_final = ft_strdup(tmp);
			free(tmp);
			break ;
		}
		free(tmp);
		j++;
	}
	return (path_final);
}
// PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin



char	*search_path(t_data *data, char **cmd_args)
{
	int		i;
	char	*path_alpha;
	char	*path_final;

	i = 0;
	path_final = NULL;
	while (data->envp[i] != NULL)
	{
		/**
		 * @brief Finding PATH and "=" variable in env
		*/
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			path_alpha = ft_strchr(data->envp[i], '=') + 1;
			if (path_alpha != NULL)
			{
				data->paths = ft_split(path_alpha, ':');
				path_final = search_final_path(data, cmd_args);
				free_malloc_split(data->paths);
				data->paths = NULL;
			}
			break ;
		}
		i++;
	}
	return (path_final);
}
