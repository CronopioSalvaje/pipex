/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:50:39 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/26 19:19:30 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include "libft/libft.h"

typedef struct s_data
{
	char *infile;
	char **cmd1;
	char *outfile;
	char **cmd2;
	char **env;
	int pid1;
	int pid2;
	int status;
} t_data;


#endif