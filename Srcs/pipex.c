/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:48:55 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/27 05:39:29 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

void	init_data(t_data *data, char **av, char **env)
{
	data->infile = av[1];
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->outfile = av[4];
	data->env = env;
	data->status = 0;
}

char	*cpy(char *src, char *dest)
{
	while (*src)
		*dest++ = *src++;
	return (dest);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*res;
	int		t_len;

	if (!s1 || !s2)
		return (NULL);
	t_len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (t_len < 1)
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else
		res = malloc(sizeof(char) * (t_len + 2));
	if (!res)
		return (NULL);
	res = cpy(s1, res);
	res = cpy(s2, res);
	return (*res = 0, free(s1), res - t_len);

}

char *read_infile(char *infile)
{
	int fd;
	char *parsed;
	char *buff;	

	fd = open(infile, O_RDONLY);
	if (!fd)
		return NULL;
	parsed = get_next_line(fd);
	buff = get_next_line(fd);
	while (buff)
	{
		parsed = ft_strjoin_and_free(parsed, buff);
		free(buff);
		buff = get_next_line(fd);
	}
	close(fd);
	return(parsed);
}




int main(int ac, char **av, char **env)
{
	t_data data;

	int fd[2];
	int fdpipe[2];
	if(pipe(fd) == -1)
		return 1;
	char *test;
	if (ac != 5)
		return (1);
	init_data(&data, av, env);
	data.pid1 = fork();
	if (data.pid1 == 0)
	{
		// ici j'execute le processus en dupliquant...
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		pipe(fdpipe);
		dup2(fdpipe[1], STDOUT_FILENO);
		data.pid2 = fork();
		if (data.pid2 == 0)
		{
			execve("/usr/bin/grep", data.cmd1, env);	
		}
		else
		{
			char buff[5000];
			read(fdpipe[0], buff, 5000);
			printf("ah %s", buff);
		}
	}
	else
	{
		close(fd[0]);
		test = read_infile(data->infile);
		write(fd[1], test, ft_strlen(test));
		free(test);
		close(fd[1]);
		waitpid(data.pid1, &data.status, 0);
	}
	return 0;

}