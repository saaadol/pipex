/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:35:20 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 00:57:09 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *envp[])
{
	pid_t	pid[2];
	int		pips[2];

	if (ac != 5)
		return (write (2, "few or more arguments\n", 22), 0);
	pipe(pips);
	pid[0] = child_fork1(av, envp, pips);
	pid[1] = child_fork2(av, envp, pips);
	close(pips[1]);
	close(pips[0]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
