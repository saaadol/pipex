/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:31:17 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 00:37:51 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_func(char **av, char *envp[], int **pips)
{
	pid_t	pid;
	pid_t	pid2;
	int		i;

	pid = bonus_child_fork_heredoc_1(av, envp, pips);
	pid2 = bonus_child_fork_heredoc_2(av, envp, pips);
	i = 0;
	while (i < 2)
	{
		close(pips[i][0]);
		close(pips[i][1]);
		i++;
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	closing_pipes(int ac, int **array)
{
	int	i;

	i = 0;
	while (i < ac -4)
	{
		close(array[i][0]);
		close(array[i][1]);
		i++;
	}
}
