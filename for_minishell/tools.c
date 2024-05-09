/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:34 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/23 14:01:51 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_malloc_split(char **dest)
{
	int	i;

	if (dest == NULL)
		return ;
	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

void	print_error(const char *var, const char *msg)
{
	size_t	var_len;
	size_t	msg_len;
	size_t	total_len;
	char	*error_msg;

	var_len = ft_strlen(var);
	msg_len = ft_strlen(msg);
	total_len = var_len + msg_len;
	error_msg = (char *)malloc(sizeof(char) * total_len + 1);
	ft_memcpy(error_msg, var, var_len);
	ft_memcpy(error_msg + var_len, msg, msg_len);
	error_msg[total_len] = '\0';
	write(STDERR_FILENO, error_msg, total_len);
	free(error_msg);
}

void	init_values_data(t_data *data)
{
	data->fds.input = 0;
	data->fds.output = 0;
	data->pipefd[0] = 0;
	data->pipefd[1] = 0;
	data->pid1 = 0;
	data->pid2 = 0;
	data->pid = 0;
	data->pid_current = 0;
	data->ac = 0;
	data->av = NULL;
	data->envp = NULL;
	data->status = 0;
	data->status1 = 0;
	data->status2 = 0;
	data->paths = NULL;
	data->cmd1_found = false;
	data->cmd2_found = false;
	data->open_result = 0;
	data->path = NULL;
	data->first_message = 0;
}

bool	can_execute(const char *filepath)
{
	return (access(filepath, X_OK) == 0);
}

void	error_execve_check(char **cmd_args)
{
	print_error(cmd_args[0], ": Permission denied\n");
	if (errno == EACCES)
		exit(126);
	else
		exit(1);
}
