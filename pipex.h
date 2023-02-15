#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/wait.h>
#include <stdlib.h>
#include "get_next_line.h"

char	**ft_free(char **str, size_t j);
char	**ft_split(char const *s, char c);
int ft_strlen(char *str);
char	*ft_newstrchr(char *s, char *target);
//char	*ft_join(char  *s1, char  *s2);
char *checking_path(char **av, char *envp[], char *comm);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_join(char *s1, char *s2);
void exec_function(char **av, char *envp[], char **command, char *x);


#endif