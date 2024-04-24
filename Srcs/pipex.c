/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:48:55 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/24 17:53:53 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

void	init_data(t_data *data, char **av, char **env)
{
	data->infile = av[1];
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->outfile = av[4];
	data->env = env;
}
/*
void	free_data(t_data *data)
{
	
}*/

void	test_env(t_data data)
{
	int i = 0;
	while (data.env[i])
	{
		printf("%s\n", data.env[i]);
		i++;
	}
}


int main(int ac, char **av, char **env)
{
	t_data data;
	int fd[2];
	(void)fd;
	if (ac != 5)
		return (1);
	init_data(&data, av, env);
	test_env(data);
	printf("%s %s %s %s\n",data.infile, data.cmd1, data.cmd2, data.outfile);
	return 0;

}