#include "pipex.h"


char	*ft_newstrchr(char *s, char *target)
{
	int	i;
	int	len;
	int j;
	len = ft_strlen(s);
	i = 0;
	j = 0;
	if(!s)
		exit(1);
	while (s[i])
	{
		if (s[i] == target[j])
			j++;
		else if (target[j] == '\0')
				return (s + i);
		i++;
	}
	return NULL;

}

char *located_path_return(char *envp[])
{
	int i;
	char *p;
	char *located_path;

	p = "PATH=";
	i = 0;
	while(envp[i])
	{
		if (ft_newstrchr(envp[i], p))
			located_path = ft_newstrchr(envp[i], p);
		i++;
	}
	if(!located_path)
		exit(1);
	return located_path;
}
char *checking_path(char **av, char *envp[], char *comm)
{
	int i;
	char *located_path;
	char **str;

	located_path = located_path_return(envp);
	str = ft_split(located_path, ':');
	if (ft_newstrchr(comm, "./"))
		return (comm);
	i = 0;
	while (str[i])
	{
		str[i] = ft_join(str[i], ft_join("/", comm));
		if (access(str[i], F_OK) == 0)
			return str[i];
		free(str[i]);
		i++;
	}
	return (free(str),NULL);
}

void exec_function(char **av, char *envp[], char **command, char *x)
{
	if (access(x, F_OK) == 0)
		{
			if (execve(command[0], command, envp) == -1)
				perror(x);
		}
		else if (execve(checking_path(av ,envp, command[0]), command, envp) == -1)
			perror(x);
}
int child_fork1(char **av, char *envp[], int *pips)
{
	pid_t pid;
	int fd;
	char **command;
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
		exec_function(av, envp, command, av[2]);
	}
	return pid;
}
int child_fork2(char **av, char *envp[], int *pips)
{
	pid_t pid2;
	char **command;
	int fd;
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
		exec_function(av, envp, command, av[3]);
	}
	return pid2;
}

// int main(int ac, char **av, char *envp[])
// {
// 	pid_t pid[2];
// 	char **split;
// 	int pips[2];
// 	char **command;
// 	if (ac != 5)
// 		return (write (2, "few or more arguments\n", 22), 0);
// 	pipe(pips);
// 	pid[0] = child_fork1(av, envp, pips);
// 	pid[1] = child_fork2(av,envp,pips);
// 	close(pips[1]);
// 	close(pips[0]);	
// 	waitpid(pid[0], NULL, 0);
// 	waitpid(pid[1], NULL, 0);
// }

