#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/wait.h>
int main(int ac, char **av)
{
	pid_t pid;
	pid_t pid2;
	int pips[2];
	char *command[] = {"cat", "-", 0};
	char *command1[] = {"wc", "-l" ,0};
	pipe(pips);
	pid = fork();
	if (pid == 0)
	{
		int fd = open("infile", O_RDONLY, 0777);
		dup2(fd, 0);
		close(fd);
		dup2(pips[1], 1);
		close(pips[1]);
		close(pips[0]);
		execvp(command[0], command);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			int fd2 = open("outfile", O_CREAT | O_TRUNC | O_WRONLY, 0777);
			dup2(fd2, 1);
			close(fd2);
			dup2(pips[0], 0);
			close(pips[1]);
			close(pips[0]);
			execvp(command1[0], command1);
		}
		else
		{
			close(pips[1]);
			close(pips[0]);	
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
}