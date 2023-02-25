/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:24:27 by souledla          #+#    #+#             */
/*   Updated: 2023/02/24 17:13:56 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_fork1(char **av, char *envp[], int *pips)
{
	int		fd;
	pid_t	pid;
	char	**command;

	pid = fork();
	if (pid == 0)
	{
		fd = open(av[1], O_RDONLY, 0777);
		command = ft_split(av[2], ' ');
		if (dup2(fd, 0) == -1)
		{
			perror(av[1]);
			exit(1);
		}
		close(fd);
		if (dup2(pips[1], 1) == -1)
			perror("Pipe:");
		close(pips[1]);
		close(pips[0]);
		exec_function(envp, command, av[2]);
	}
	return (pid);
}

int	child_fork2(char **av, char *envp[], int *pips)
{
	pid_t	pid2;
	char	**command;
	int		fd;

	pid2 = fork();
	if (pid2 == 0)
	{
		fd = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		command = ft_split(av[3], ' ');
		if (dup2(fd, 1) == -1)
		{
			perror(av[4]);
			exit(1);
		}
		close(fd);
		if (dup2(pips[0], 0) == -1)
			perror("Pipe:");
		close(pips[1]);
		close(pips[0]);
		exec_function(envp, command, av[3]);
	}
	return (pid2);
}
