
#include "pipex.h"

// pipes = ac - 4
int **handling_multiple_pipes(int ac)
{
	int number_of_pipes = ac - 4; 
	int i = 0;
	int **array_of_pipes;
	array_of_pipes	 = malloc(sizeof(int *) * (number_of_pipes));
	while (i < number_of_pipes)
	{
		array_of_pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return array_of_pipes;
}
int main(int ac, char **av, char *envp[])
{
	int fd1;
	int fd2;
	int **array;
	pid_t f1;
	pid_t f2; 
	char **split;
	int i;
	int j = 0;
	pid_t fn;
	int x = 0;
	int y = 1;

	array = handling_multiple_pipes(ac);
	i = 0;
	while (i < ac -4)
	{
		pipe(array[i]);
		i++;
	}
	i = 0;
	f1 = fork();
	if (f1 == 0)
	{
		fd1 = open(av[1],  O_RDONLY, 0777);
		split = ft_split(av[2], ' ');
		char *command[] = {split[0], split[1], 0};
		dup2(fd1, 0);
		close(fd1);
		dup2(array[0][1], 1);
		while(i < ac -4)
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		execve(checking_path(av, envp, split[0]), command, envp);
	}
	while (j < ac - 5) 
	{
		fn = fork();
		if (fn == 0)
		{
			split = ft_split(av[3 + j], ' ');
			char *command[] = {split[0], split[1], 0};
			dup2(array[j][0], 0);
			dup2(array[j + 1][1], 1);
			while (i < ac - 4)
			{
				close(array[i][0]);
				close(array[i][1]);
				i++;
			}
			execve(checking_path(av, envp, split[0]), command, envp);
		}
		j++;
	}

	// else
	// {
		f2 = fork();
		if (f2 == 0)
		{
			fd2 = open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY , 0777);
			split = ft_split(av[ac - 2], ' ');	
			char *command1[] = {split[0], split[1], 0};
			dup2(fd2, 1);
			close(fd2);
			dup2(array[j][0], 0);
			i =0;
			while(i < ac - 4 )
			{
				close(array[i][0]);
				close(array[i][1]);
				i++;
			}
			execve(checking_path(av, envp, split[0]), command1, envp);
		}
		else
		{
			i = 0;
			while(i < ac -4)
			{
				close(array[i][0]);
				close(array[i][1]);
				i++;
			}
			waitpid(f1, NULL, 0);
			waitpid(fn, NULL, 0);
			waitpid(f2, NULL, 0);
		}
		

	}
//}
