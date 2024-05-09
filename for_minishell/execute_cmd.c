/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:16 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/23 14:59:26 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_cmd_args(char **cmd_args, t_data *data)
{
	int	i;

	if (cmd_args == NULL || cmd_args[0] == NULL)
	{
		write(STDERR_FILENO, "Command not found\n", 18);
		free_malloc_split(cmd_args);
		/**
		 * @brief It's was an exceptional error case, it exits in code 0 for child1 and 127 for child2.
		 * @attention You're going to see more exit methods in the child process command execution
		*/
		if (data->pid == data->pid1)
			exit(0);
		else
			exit(127);
	}
	i = 0;
	while (cmd_args[i] != NULL)
	{
		/**
		 * @brief It checks if av[2] or av[3] is available, it works only where the cmd is something like this "/bin/catasdas"
		*/
		if (ft_strchr(cmd_args[i], '/') != NULL && access(cmd_args[i], F_OK) ==
			-1)
		{
			/**
			 * @attention data->first_message is just a variable used to prevent duplicates error message (see line 136 or print_messages_error function)
			*/
			data->first_message = 1;
			print_error(cmd_args[i], ": No such file or directory\n");
		}
		i++;
	}
}

static void	path_final_execution(t_data *data, char *path_final,
		char **cmd_args, int null_fd)
{
	/**
	 * @brief search path is something like "UNE USINE A GAZ", take a look of each function in search_path
	*/
	path_final = search_path(data, cmd_args);
	if (path_final != NULL && access(path_final, X_OK) == 0)
	{
		if (execve(path_final, cmd_args, data->envp) == -1)
		{
			/**
			 * @brief Here belows is the important part that i have to explain to you personally
			*/
			if (data->fds.input == -1)
			{
				dup2(STDERR_FILENO, null_fd);
				close(null_fd);
			}
			error_execve_check(cmd_args);
		}
	}
}

static void	check_cmd_access_final_path(char **cmd_args, char *path_final,
		t_data *data)
{
	/***
	 * @attention @attention This part is so important, i have to explain it personally
	*/
	int	null_fd;

	if (data->fds.input == -1)
	{
		null_fd = open("/dev/null", O_CREAT);
		dup2(null_fd, STDERR_FILENO);
		close(null_fd);
	}
	/**
	 * @brief First try to see if the cmd is available, if not, we are gonna find the real path in path_final_execution
	*/
	if (access(cmd_args[0], X_OK) == 0)
	{
		if (execve(cmd_args[0], cmd_args, data->envp) == -1)
			error_execve_check(cmd_args);
	}
	else
		path_final_execution(data, path_final, cmd_args, null_fd);
}

static void	print_messages_error(char **cmd_args, t_data *data)
{
	if (ft_strchr(cmd_args[0], '/') != NULL && access(cmd_args[0], F_OK) == -1
		&& data->first_message != 1)
		print_error(cmd_args[0], ": No such file or directory\n");
	else if (ft_strchr(cmd_args[0], '/') == NULL && access(cmd_args[0], F_OK) ==
		-1 && data->first_message != 1)
		print_error(cmd_args[0], ": Command not found\n");
}

void	execute_cmd(char *cmd, t_data *data)
{
	char	**cmd_args;
	char	*path_final;

	path_final = NULL;
	if (cmd != NULL && ft_strncmp(cmd, "", 1) != 0)
	{
		/**
		 * @brief ft_split fonction takes each str from av[2] or av[3]
		*/
		cmd_args = ft_split(cmd, ' ');
		/**
		 * @brief First checking for cmd_args(splited of av[2] or av[3])
		*/
		check_cmd_args(cmd_args, data);
		/**
		 * @brief If the first str is for exemple /usr/bin/cat it gonna execve immediatly, otherwise, the program will search the final path (path_final)
		*/
		check_cmd_access_final_path(cmd_args, path_final, data);
		/**
		 * @brief it the program continues the execution here, it means that the command cmd1 or cmd2 couldn't be execute in execve
		 * @attention so, this part of code kill the process with the correct code error and message
		*/
		print_messages_error(cmd_args, data);
		free_malloc_split(cmd_args);
		data->first_message = 0;
		if (path_final != NULL)
			free(path_final);
		if (data->pid == data->pid1)
			exit(0);
		else
			exit(127);
	}
}
