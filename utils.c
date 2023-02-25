/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:27:35 by souledla          #+#    #+#             */
/*   Updated: 2023/02/24 19:11:18 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_newstrchr(char *s, char *target)
{
	int	i;
	int	len;
	int	j;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!s)
		exit(1);
	while (s[i])
	{
		if (s[i] == target[j])
			j++;
		else if (target[j] == '\0')
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*located_path_return(char *envp[])
{
	int		i;
	char	*p;
	char	*located_path;

	p = "PATH=";
	i = 0;
	while (envp[i])
	{
		if (ft_newstrchr(envp[i], p))
			located_path = ft_newstrchr(envp[i], p);
		i++;
	}
	if (!located_path)
		exit(1);
	return (located_path);
}

char	*checking_path(char *envp[], char *comm)
{
	int		i;
	char	*located_path;
	char	**str;

	located_path = located_path_return(envp);
	str = ft_split(located_path, ':');
	i = 0;
	if (ft_newstrchr(comm, "./") || ft_newstrchr(comm, "/"))
		return (comm);
	while (str[i])
	{
		str[i] = ft_join(str[i], ft_join("/", comm));
		if (access(str[i], F_OK) == 0)
			return (str[i]);
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}

void	print_error(void)
{
	perror("nice try ;D");
	exit(1);
}

void	exec_function(char *envp[], char **command, char *x)
{
	int	fd;

	fd = open(command[0], O_RDONLY, 0777);
	if (ft_strlen(x) == 0)
		print_error();
	if (fd < 0)
	{
		if (access(x, F_OK) == 0)
		{
			close(fd);
			if (execve(command[0], command, envp) == -1)
			{
				perror(x);
				exit(1);
			}	
		}
	}
	if (execve(checking_path(envp, command[0]), command, envp) == -1)
	{	
		close(fd);
		perror(x);
		exit(1);
	}
}
