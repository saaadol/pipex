
#include "pipex.h"


void pipex_func(int ac , char **av , char *envp[], int **pips)
{
	pid_t pid;
	pid_t pid2;
	char **split;
	char *str;
	int fd;
	int fd2;
	char **command;
	char **command1;
	int i;

	pid = fork();
	if (pid == 0)
	{
		split = ft_split(av[3], ' ');
		char *command[] = {split[0] ,split[1], 0};
		if (dup2(pips[0][0], 0) == -1)
		{
			perror(av[1]);
			exit(1);
		}
		if (dup2(pips[1][1], 1) == -1)
			perror("Pipe:");
		int i = 0;
		while (i < 2)
		{
			close(pips[i][0]);
			close(pips[i][1]);
			i++;

		}
		if (access(av[3], F_OK) == 0)
		{
			if (execve(split[0], command, envp) == -1)
				perror(av[3]);
		}
		else if (execve(checking_path(av ,envp, split[0]), command, envp) == -1)
			perror(av[3]);
	}
	
		pid2 = fork();
		if (pid2 == 0)
		{
			fd2 = open(av[5], O_CREAT | O_TRUNC | O_WRONLY, 0777);
			split = ft_split(av[4], ' ');
			char *command1[] = {split[0], split[1], 0};
			if (dup2(fd2, 1) == -1)
			{
				perror(av[5]);
				exit(1);
			}
			close(fd2);
			if (dup2(pips[1][0], 0) == -1)
				perror("Pipe:");
			
		 	i = 0;
			while (i < 2)
			{	
				close(pips[i][0]);
				close(pips[i][1]);
				i++;
			}
			if (access(av[4], F_OK) == 0)
			{
				if (execve(split[0], command1, envp) == -1)
					perror(av[4]);
			}
			else if(execve(checking_path(av ,envp, split[0]), command1, envp) == -1)
			{
				perror(av[4]);
				exit(1);
			}
		}
		else
		{
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
}
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
void heredoc(int ac , char **av , char *envp[])
{
	int **pips;
	pips  = malloc(sizeof(int *)  * 2);
	int i = 0;
	while (pips[i])
	{
		pips[i]= malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while(i < 2)
	{
		pipe(pips[i]);
		i++;
	}

	char *buffer;
	char *joined = ft_join(av[2], "\n");
	while(1)
	{
		write(1, "heredoc>", 8);
		buffer = get_next_line(0);
		if(!ft_strncmp(buffer, joined, ft_strlen(joined)))
			break;
		write(pips[0][1], buffer, ft_strlen(buffer));
	}
	pipex_func(ac, av, envp, pips);
}
// int main(int ac, char **av, char *envp[])
// {
// 	int fd1;
// 	int fd2;
// 	int **array;
// 	pid_t f1;
// 	pid_t f2; 
// 	char **split;
// 	int i;
// 	int j = 0;
// 	pid_t fn;
// 	int x = 0;
// 	int y = 1;

// 	if(!(ft_strncmp(av[1], "here_doc",ft_strlen("here_doc"))))
// 	{
// 		heredoc(ac, av,envp);
// 		exit(1);
// 	}
// 	array = handling_multiple_pipes(ac);
// 	i = 0;
// 	while (i < ac -4)
// 	{
// 		pipe(array[i]);
// 		i++;
// 	}
// 	i = 0;
// 	f1 = fork();
// 	if (f1 == 0)
// 	{
// 		fd1 = open(av[1],  O_RDONLY, 0777);
// 		split = ft_split(av[2], ' ');
// 		char *command[] = {split[0], split[1], 0};
// 		dup2(fd1, 0);
// 		close(fd1);
// 		dup2(array[0][1], 1);
// 		while(i < ac -4)
// 		{
// 			close(array[i][0]);
// 			close(array[i][1]);
// 			i++;
// 		}
// 		execve(checking_path(av, envp, split[0]), command, envp);
// 	}
// 	while (j < ac - 5) 
// 	{
// 		fn = fork();
// 		if (fn == 0)
// 		{
// 			split = ft_split(av[3 + j], ' ');
// 			char *command[] = {split[0], split[1], 0};
// 			dup2(array[j][0], 0);
// 			dup2(array[j + 1][1], 1);
// 			while (i < ac - 4)
// 			{
// 				close(array[i][0]);
// 				close(array[i][1]);
// 				i++;
// 			}
// 			execve(checking_path(av, envp, split[0]), command, envp);
// 		}
// 		j++;
// 	}

// 		f2 = fork();
// 		if (f2 == 0)
// 		{
// 			fd2 = open(av[ac -1], O_CREAT | O_TRUNC | O_WRONLY , 0777);
// 			split = ft_split(av[ac - 2], ' ');	
// 			char *command1[] = {split[0], split[1], 0};
// 			dup2(fd2, 1);
// 			close(fd2);
// 			dup2(array[j][0], 0);
// 			i =0;
// 			while(i < ac - 4 )
// 			{
// 				close(array[i][0]);
// 				close(array[i][1]);
// 				i++;
// 			}
// 			execve(checking_path(av, envp, split[0]), command1, envp);
// 		}
// 		else
// 		{
// 			i = 0;
// 			while(i < ac -4)
// 			{
// 				close(array[i][0]);
// 				close(array[i][1]);
// 				i++;
// 			}
// 			waitpid(f1, NULL, 0);
// 			waitpid(fn, NULL, 0);
// 			waitpid(f2, NULL, 0);
// 		}
		

// }

