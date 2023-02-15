
#include "pipex.h"

void bonus_command_exec(char **av, char *envp[], char **command, char *x)
{
	if (access(x, F_OK) == 0)
		{
			if (execve(command[0], command, envp) == -1)
				perror(x);
		}
		else if (execve(checking_path(av ,envp, command[0]), command, envp) == -1)
			perror(x);
}

void closing_pipes_herdoc(int **pips)
{
	int i;

	i = 0;
	while (i < 2)
	{
		close(pips[i][0]);
		close(pips[i][1]);
		i++;
	}
}
pid_t bonus_child_fork_heredoc_1(char **av, char *envp[], int **pips)
{
	pid_t pid;
	char **command;

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
		
		bonus_command_exec(av, envp, command, av[3]);
	}
	return pid;
}
pid_t bonus_child_fork_heredoc_2(char **av, char *envp[], int **pips)
{
	pid_t pid2;
	int fd2;
	char **command1;
	int i;

	i = 0;
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
			
		 	i = 0;
			while (i < 2)
			{	
				close(pips[i][0]);
				close(pips[i][1]);
				i++;
			}
			bonus_command_exec(av, envp, command1, av[4]);
		}
		return pid2;
}
void pipex_func(int ac , char **av , char *envp[], int **pips)
{
	pid_t pid;
	pid_t pid2;
	int i;

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
int **handling_multiple_pipes(int ac)
{
	int number_of_pipes;
	int **array_of_pipes;
	int i;
	
	number_of_pipes = ac - 4; 
	i = 0;
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
	int i;
	char *buffer;
	char *joined;
	
	i = 0;
	pips  = malloc(sizeof(int *)  * 2);
	while (pips[i])
		pips[i++]= malloc(sizeof(int) * 2);
	i = 0;
	while(i < 2)
		pipe(pips[i++]);
	joined = ft_join(av[2], "\n");
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
pid_t bonus_child_fork_1(int ac, char **av, char *envp[], int **array)	
{
	pid_t f1;
	int fd1;
	char **command;
	int i; 

	i = 0;
	f1 = fork();
	if (f1 == 0)
	{
		fd1 = open(av[1],  O_RDONLY, 0777);
		command = ft_split(av[2], ' ');
		if (dup2(fd1, 0) == -1)
		{
			perror(av[1]);
			exit(1);
		}
		close(fd1);
		if (dup2(array[0][1], 1) == -1)
			perror("Pipe:");
		while(i < ac -4)
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		execve(checking_path(av, envp, command[0]), command, envp);
		exec_function(av, envp, command, av[2]);
	}
	return f1;
}
pid_t bonus_child_fork_2(int *arr, char **av, char *envp[], int **array)
{
	pid_t f2;
	int fd2;
	int i;
	char **command;
	f2 = fork();
	if (f2 == 0)
	{
		fd2 = open(av[arr[0] -1], O_CREAT | O_TRUNC | O_WRONLY , 0777);
		command = ft_split(av[arr[0] - 2], ' ');	
		dup2(fd2, 1);
		close(fd2);
		dup2(array[arr[1]][0], 0);
		i =0;
		while(i < arr[0] - 4)
		{
			close(array[i][0]);
			close(array[i][1]);
			i++;
		}
		execve(checking_path(av, envp, command[0]), command, envp);
	}
	return f2;

}
int while_loop_fork(int *arr, char **av, char *envp[],  int **array)
{
	pid_t fn;
	int i = 0;
	char **command;
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
			execve(checking_path(av, envp, command[0]), command, envp);
		}
		(arr[1])++;
	}
	return(fn);
}
void closing_pipes(int ac, int *arr, int **array)
{
	int i;

	i = 0;
	while(i < ac -4)
	{
		close(array[i][0]);
		close(array[i][1]);
		i++;
	}
}
void waiting_pid(pid_t f1, pid_t fn, pid_t f2)
{
	waitpid(f1, NULL, 0);
	waitpid(fn, NULL, 0);
	waitpid(f2, NULL, 0);
}
void checking_ac_length(int ac)
{
	if (ac < 5)
	{
		write(2,"few or more arguments\n", 22);
		exit(1);
	}
}
void checking_ac_length_for_herdoc(int ac)
{
	if (ac != 6)
	{
		write(2,"few or more arguments\n", 22);
		exit(1);
	}
}
int main(int ac, char **av, char *envp[])
{
	int **array;
	pid_t f1;
	pid_t f2; 
	pid_t fn;
	int arr[4];

	arr[0] = ac;
	if(!(ft_strncmp(av[1], "here_doc",ft_strlen("here_doc"))))
	{
		checking_ac_length_for_herdoc(ac);			 
		heredoc(ac, av,envp);
		exit(1);
	}
	checking_ac_length(ac);
	array = handling_multiple_pipes(ac);
	arr[2] = 0;
	while (arr[2] < ac -4)
		pipe(array[(arr[2])++]);
	f1 = bonus_child_fork_1(ac ,av, envp, array);
	fn = while_loop_fork(arr, av, envp, array); 
	f2 = bonus_child_fork_2(arr, av , envp, array);
	closing_pipes(ac, arr, array);
	waiting_pid(f1, fn, f2);
}



