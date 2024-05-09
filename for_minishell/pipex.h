/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:11:08 by dagudelo          #+#    #+#             */
/*   Updated: 2024/04/23 15:01:01 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include "./libft/libft.h"

/**
 * @brief Libft modified : ft_strlcat
 * @attention if you want to see the values of each variable, you need to use fprintf(stderr, "%s\n", str);
 * @attention the test program has to be execute like "bash tester_pipex.sh"
 * 
*/

/**
 * @brief input and output descriptors (infile and outfile)
*/
typedef struct s_file_descriptors
{
	int		input;
	int		output;
}			t_fds;

/**
 * @brief 	Simple database to manage each variable in the fonctions
 * @param 	fds Structure to store the input and output ID
 * @param 	pipefd[2] Pipe fonction to store input [0] (writing in the pipe) and output [1] (reading in the pipe)
 * @param 	pid1 ID of the first child (cmd1)
 * @param 	pid2 ID of the second child (cmd2)
 * @param 	pid ID of the current child process in the fonction setup_child_process, It's to manage each exit_status code in case of error
 * @param 	pid_current ID of the current child process OUT setup_child_process
 * @param 	ac argc variable
 * @param 	av argv variable
 * @param 	envp variables from envp
 * @param 	status integer sent in the waitpid variable to recover the code of exit_status
 * @param 	status1 once data.status is recovered, we can put the code of child1 (pid1) to status1
 * @param 	status2 once data.status is recovered, we can put the code of child1 (pid1) to status2
 * @param 	paths it's to store each str of the path to find, it finds into the relatives paths and env
 * @param 	cmd1_found its a simple check to see if cmd1 and cmd2 exist, its just for managing the exceptionnal case of error
 * @param 	cmd2_found same as cmd1_found
 * @param 	open_result open result is just to store the code from open() function, for managing the error cases
 * @param 	path it stores the command path search_path, see the check_two_args fonction, it's about cmd1_found and cmd2_found
 * @param 	first_message Exceptional case to print the error message in case the cmd1 doesn't exist
*/

typedef struct s_data
{
	t_fds	fds;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid;
	pid_t	pid_current;
	int		ac;
	char	**av;
	char	**envp;
	int		status;
	int		status1;
	int		status2;
	char	**paths;
	bool	cmd1_found;
	bool	cmd2_found;
	int		open_result;
	char	*path;
	int		first_message;
}			t_data;


/* Main functions */

void		create_pid_process(t_data *data);


/* Setup functions */

void		open_fd_and_pipes(t_data *data);
pid_t		create_child_process(t_fds fds, char *cmd, t_data *data);
int			open_files(t_data *data);

/* Find cmd path */

char		*search_path(t_data *data, char **cmd_args);


/* Execute cmd functions */

void		execute_cmd(char *cmd, t_data *data);


/* Check two cmds and close pipes and files  */

bool		check_two_args(char *cmd1, char *cmd2, t_data *data);
void		close_pipes_and_files(t_data *data);

/* Handle exit status codes */

void		handle_exit(int *exit_status1, int *exit_status2, t_data *data);

/* Tools functions */

void		free_malloc_split(char **dest);
void		print_error(const char *var, const char *msg);
void		init_values_data(t_data *data);
bool		can_execute(const char *filepath);
void		error_execve_check(char **cmd_args);

/* Function to add into Libft */

char		*ft_strstr(char *str, char *to_find);


#endif