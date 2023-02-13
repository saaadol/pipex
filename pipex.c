#include "pipex.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
char	*ft_strchr(char *s, char *target)
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

char *checking_path(char **av, char *envp[], char *comm)
{
	int i = 0;
  	char *p = "PATH=";
	char *located_path;
	char **str;
	while(envp[i])
	{
		if (ft_strchr(envp[i], p))
			located_path = ft_strchr(envp[i], p);
		i++;
	}
	if(!located_path)
		exit(1);
	str = ft_split(located_path, ':');
	i = 0;
	if (ft_strchr(comm, "./"))
		return (comm);
	while (str[i])
	{
		str[i] = ft_strjoin(str[i], ft_strjoin("/", comm));
		if (access(str[i], F_OK) == 0)
			return str[i];
		free(str[i]);
		i++;
	}
	free(str);
	return NULL;
}

// int main(int ac, char **av, char *envp[])
// {
// 	pid_t pid;
// 	pid_t pid2;
// 	char **split;
// 	char *str;
// 	int pips[2];
// 	int fd;
// 	int fd2;
// 	char **command;
// 	char ** command1;
// 	if (ac != 5)
// 		return (write (2, "few or more arguments\n", 22), 0);
// 	pipe(pips);

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		fd = open(av[1], O_RDONLY, 0777);
// 		split = ft_split(av[2], ' ');
// 		char *command[] = {split[0] ,split[1], 0};
// 		if (dup2(fd, 0) == -1)
// 			perror(av[1]);
// 		close(fd);
// 		if (dup2(pips[1], 1) == -1)
// 			perror("Pipe:");
// 		close(pips[1]);
// 		close(pips[0]);
// 		if (access(av[2], F_OK) == 0)
// 		{
// 			if (execve(split[0], command, envp) == -1)
// 				perror(av[2]);
// 		}
// 		else if (execve(checking_path(av ,envp, split[0]), command, envp) == -1)
// 			perror(av[2]);
// 	}
	
// 		pid2 = fork();
// 		if (pid2 == 0)
// 		{
// 			fd2 = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
// 			split = ft_split(av[3], ' ');
// 			char *command1[] = {split[0], split[1], 0};
// 			if (dup2(fd2, 1) == -1)
// 			{
// 				perror(av[4]);
// 				exit(1);
// 			}
// 			close(fd2);
// 			if (dup2(pips[0], 0) == -1)
// 				perror("Pipe:");
// 			close(pips[1]);
// 			close(pips[0]);
// 			if (access(av[3], F_OK) == 0)
// 			{
// 				if (execve(split[0], command1, envp) == -1)
// 					perror(av[3]);
// 			}
// 			else if(execve(checking_path(av ,envp, split[0]), command1, envp) == -1)
// 			{
// 				perror(av[3]);
// 				exit(1);
// 			}
// 		}
// 		else
// 		{
// 			close(pips[1]);
// 			close(pips[0]);	
// 			waitpid(pid, NULL, 0);
// 			waitpid(pid2, NULL, 0);
// 		}
	
// }

