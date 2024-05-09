/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_fds_child_setup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:09:51 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:45 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/**
 * @brief It takes all the times the input (writing side) to swap the standard input and output.
 * @attention child1 swaps fds.input(infile) with pipefd[1]
 * @attention child2 swaps normally pipefd[0] with fds.output(outfile)
*/

static void	setup_child_process(t_fds fds, char *cmd, t_data *data)
{
	if (fds.input != -1)
	{
		dup2(fds.input, STDIN_FILENO);
		close(fds.input);
	}
	if (fds.output != -1)
	{
		dup2(fds.output, STDOUT_FILENO);
		close(fds.output);
	}
	if (data->pipefd[0] != -1)
		close(data->pipefd[0]);
	if (data->pipefd[1] != -1)
		close(data->pipefd[1]);
	/**
	 * @brief It takes cmd1 and cmd2, or av[2] and av[3]
	*/
	execute_cmd(cmd, data);
}

/**
 * @brief Usage of fork function to create new process (child1 and child2)
 * @attention if pid == 0 or (pid1 and pid2), it means that it's a child process
*/

pid_t	create_child_process(t_fds fds, char *cmd, t_data *data)
{
	pid_t	pid;

	pid = fork();
	data->pid = pid;
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		setup_child_process(fds, cmd, data);
	if (fds.input != -1)
		close(fds.input);
	if (fds.output != -1)
		close(fds.output);
	return (pid);
}

void	open_fd_and_pipes(t_data *data)
{
	errno = 0;
	data->fds.input = open(data->av[1], O_RDONLY);
	if (data->fds.input < 0)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		data->fds.input = -1;
		errno = 0;
	}
	if (data->fds.input != -1)
	{
		if (pipe(data->pipefd) == -1)
		{
			perror("pipe");
			if (data->fds.input != -1)
				close(data->fds.input);
			if (data->fds.output != -1)
				close(data->fds.output);
			exit(EXIT_FAILURE);
		}
	}
}

int	open_files(t_data *data)
{
	errno = 0;
	data->fds.output = open(data->av[data->ac - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds.output < 0)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		if (errno == EACCES)
			exit(1);
		errno = 0;
		return (1);
	}
	return (0);
}
