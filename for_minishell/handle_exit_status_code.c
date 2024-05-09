/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_status_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:26:45 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/23 13:56:26 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_exit_status1(int *exit_status1, t_data *data)
{
	if (WIFEXITED(data->status1))
	{
		*exit_status1 = WEXITSTATUS(data->status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (data->fds.input == -1 && data->fds.output != -1)
			*exit_status1 = 0;
	}
	else if (WIFSIGNALED(data->status1))
	{
		*exit_status1 = 128 + WTERMSIG(data->status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		if (data->fds.input == -1 && data->fds.output != -1)
			*exit_status1 = 0;
	}
	else
	{
		if (check_two_args(data->av[2], data->av[3], data) == false)
			*exit_status1 = 127;
		else
			*exit_status1 = 0;
	}
}

static void	handle_exit_status2(int *exit_status2, t_data *data)
{
	if (WIFEXITED(data->status2))
	{
		*exit_status2 = WEXITSTATUS(data->status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (data->fds.input == -1 && data->fds.output != -1)
			*exit_status2 = 0;
	}
	else if (WIFSIGNALED(data->status2))
	{
		*exit_status2 = 128 + WTERMSIG(data->status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (data->fds.input == -1 && data->fds.output != -1)
			*exit_status2 = 0;
	}
}

void	handle_exit(int *exit_status1, int *exit_status2, t_data *data)
{
	data->pid_current = waitpid(-1, &data->status, 0);
	while (data->pid_current > 0)
	{
		if (data->pid_current == data->pid1)
			data->status1 = data->status;
		else if (data->pid_current == data->pid2)
			data->status2 = data->status;
		data->pid_current = waitpid(-1, &data->status, 0);
	}
	handle_exit_status1(exit_status1, data);
	handle_exit_status2(exit_status2, data);
}
