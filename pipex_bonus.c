/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:52:46 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 00:55:29 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	protection(int ac)
{
	if (ac < 5)
	{
		write(2, "few or more arugemnts\n", 23);
		exit(1);
	}
}

int	main(int ac, char **av, char *envp[])
{
	int		**array;
	pid_t	f1;
	pid_t	f2;
	pid_t	fn;
	int		arr[4];

	protection(ac);
	arr[0] = ac;
	arr[1] = 0;
	if (!(ft_strncmp(av[1], "here_doc", ft_strlen("here_doc"))))
	{
		heredoc(ac, av, envp);
		exit(1);
	}
	array = handling_multiple_pipes(ac);
	arr[2] = 0;
	while (arr[2] < ac -4)
		pipe(array[(arr[2])++]);
	f1 = bonus_child_fork_1(ac, av, envp, array);
	fn = while_loop_fork(arr, av, envp, array);
	f2 = bonus_child_fork_2(arr, av, envp, array);
	closing_pipes(ac, array);
	waiting_pid(f1, fn, f2);
}
