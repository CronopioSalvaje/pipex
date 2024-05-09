/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:31 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/27 05:51:27 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pid_process(t_data *data)
{
	/**
	 * @brief Creation of child1 process sending writing pipe[1], file descriptor of input and the first command
	*/
	if (data->fds.input != -1)
	{
		data->pid1 = create_child_process((t_fds){data->fds.input,
				data->pipefd[1]}, data->av[2], data); /////// WTF ????
		if (data->pid1 == -1)
		{
			perror("fork");
			close_pipes_and_files(data);
			exit(EXIT_FAILURE);
		}
	}
	/**
	 * @attention Openning output descriptor after child1 execution, we save the exit code after execve of child2 or cmd2
	*/
	data->open_result = open_files(data);
	/**
	 * @attention Creation of child2 in two cases, if there is an error opening input file, we gonna send it directly in child2 without execution of child1
	*/
	if (data->fds.input != -1)
		data->pid2 = create_child_process((t_fds){data->pipefd[0],
				data->fds.output}, data->av[3], data);
	else
		data->pid2 = create_child_process((t_fds){data->fds.input,
				data->fds.output}, data->av[3], data);
	if (data->pid2 == -1)
	{
		perror("fork");
		close_pipes_and_files(data);
		exit(EXIT_FAILURE);
	}
}


int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		exit_status1;
	int		exit_status2;

	/**
	 * @brief Declare and initialize the variables in data
	*/
	init_values_data(&data);
	data.ac = ac;
	data.av = av;
	data.envp = envp;
	/**
	 * @brief Restriction of number of arguments
	*/
	if (data.ac != 5)
		return (1);
	/**
	 * @brief Open JUST infile document and save the file descriptor into data->fds.input.
	 * @param data->pipefd stores and create the first pipe.
	*/
	open_fd_and_pipes(&data);
	/**
	 * @brief Process creation of childs
	*/
	create_pid_process(&data);
	/**
	 * @brief See the in create_pid_process we save the return exit code just for OUTPUT of cmd2 code. And here we execute the return command with the parent process
	*/
	if (data.open_result)
		return (data.open_result);
	/**
	 * @brief It checks the permission access to the directory of cmd2 at the end
	*/
	if (!can_execute(data.av[3]) && ft_strstr(data.av[3], "./") != NULL)
		return (print_error(data.av[3], ": Permission denied\n"), 126);
	/**
	 * @brief Management of exit_status code for pid1 and pid2
	*/
	handle_exit(&exit_status1, &exit_status2, &data);
	/**
	 * @brief Final return execution
	*/
	if (exit_status1 != 0)
		return (exit_status1);
	else if (exit_status2 != 0)
		return (exit_status2);
}
