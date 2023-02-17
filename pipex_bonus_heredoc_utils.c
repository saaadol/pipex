/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_heredoc_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:16:34 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 00:47:17 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	bonus_child_fork_heredoc_1(char **av, char *envp[], int **pips)
{
	pid_t	pid;
	char	**command;

	pid = fork();
	if (pid == 0)
	{
		command = ft_split(av[3], ' ');
		if (dup2(pips[0][0], 0) == -1)
		{
			perror(av[1]);
			exit(1);
		}
		if (dup2(pips[1][1], 1) == -1)
			perror("Pipe:");
		closing_pipes_herdoc(pips);
		exec_function(envp, command, av[3]);
	}
	return (pid);
}

pid_t	bonus_child_fork_heredoc_2(char **av, char *envp[], int **pips)
{
	pid_t	pid2;
	int		fd2;
	char	**command1;

	pid2 = fork();
	if (pid2 == 0)
	{
		fd2 = open(av[5], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		command1 = ft_split(av[4], ' ');
		if (dup2(fd2, 1) == -1)
		{
			perror(av[5]);
			exit(1);
		}
		close(fd2);
		if (dup2(pips[1][0], 0) == -1)
			perror("Pipe:");
		closing_pipes_herdoc(pips);
		exec_function(envp, command1, av[4]);
	}
	return (pid2);
}

void	heredoc(int ac, char **av, char *envp[])
{
	int		**pips;
	int		i;
	char	*buffer;
	char	*joined;

	if (ac != 6)
		return ;
	i = 0;
	pips = malloc(sizeof(int *) * 2);
	while (pips[i])
		pips[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while (i < 2)
		pipe(pips[i++]);
	joined = ft_join(av[2], "\n");
	while (1)
	{
		write(1, "heredoc>", 8);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, joined, ft_strlen(joined)))
			break ;
		write(pips[0][1], buffer, ft_strlen(buffer));
	}
	pipex_func(av, envp, pips);
}

void	bonus_command_exec(char *envp[], char **command, char *x)
{
	if (access(x, F_OK) == 0)
	{
		if (execve(command[0], command, envp) == -1)
			perror(x);
	}
	else if (execve(checking_path(envp, command[0]), command, envp) == -1)
		perror(x);
}

void	closing_pipes_herdoc(int **pips)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		close(pips[i][0]);
		close(pips[i][1]);
		i++;
	}
}
