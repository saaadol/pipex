/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:10:58 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 01:01:03 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**handling_multiple_pipes(int ac)
{
	int	number_of_pipes;
	int	**array_of_pipes;
	int	i;

	number_of_pipes = ac - 4;
	i = 0;
	array_of_pipes = malloc(sizeof(int *) * (number_of_pipes));
	while (i < number_of_pipes)
	{
		array_of_pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (array_of_pipes);
}

int	while_loop_fork(int *arr, char **av, char *envp[], int **array)
{
	pid_t	fn;
	int		i;
	char	**command;

	i = 0;
	while (arr[1] < arr[0] - 5)
	{
		fn = fork();
		if (fn == 0)
		{
			command = ft_split(av[3 + arr[1]], ' ');
			dup2(array[arr[1]][0], 0);
			dup2(array[arr[1] + 1][1], 1);
			while (i < arr[0] - 4)
			{
				close(array[i][0]);
				close(array[i][1]);
				i++;
			}
			exec_function(envp, command, av[3 + arr[1]]);
		}
		(arr[1])++;
	}
	return (fn);
}

pid_t	bonus_child_fork_1(int ac, char **av, char *envp[], int **array)
{
	pid_t	f1;
	int		fd1;
	char	**command;
	int		i;

	i = 0;
	f1 = fork();
	if (f1 == 0)
	{
		fd1 = open(av[1], O_RDONLY, 0777);
		command = ft_split(av[2], ' ');
		if (dup2(fd1, 0) == -1)
		{
			perror(av[1]);
			exit(1);
		}
		close(fd1);
		if (dup2(array[0][1], 1) == -1)
			perror("Pipe:");
		closing_pipes(ac, array);
		execve(checking_path(envp, command[0]), command, envp);
		exec_function(envp, command, av[2]);
	}
	return (f1);
}

pid_t	bonus_child_fork_2(int *arr, char **av, char *envp[], int **array)
{
	pid_t	f2;
	int		fd2;
	int		i;
	char	**command;

	f2 = fork();
	if (f2 == 0)
	{
		fd2 = open(av[arr[0] -1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		command = ft_split(av[arr[0] - 2], ' ');
		dup2(fd2, 1);
		close(fd2);
		dup2(array[arr[1]][0], 0);
		i = 0;
		while (i < arr[0] - 4)
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		exec_function(envp, command, av[arr[0] - 2]);
	}
	return (f2);
}

void	waiting_pid(pid_t f1, pid_t fn, pid_t f2)
{
	waitpid(f1, NULL, 0);
	waitpid(fn, NULL, 0);
	waitpid(f2, NULL, 0);
}
