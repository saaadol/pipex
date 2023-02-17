/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:57:59 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 00:59:54 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "get_next_line.h"

char	**ft_free(char **str, size_t j);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *str);
char	*ft_newstrchr(char *s, char *target);
char	*checking_path(char *envp[], char *comm);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_join(char *s1, char *s2);
void	exec_function(char *envp[], char **command, char *x);
int		child_fork1(char **av, char *envp[], int *pips);
int		child_fork2(char **av, char *envp[], int *pips);
int		**handling_multiple_pipes(int ac);
int		while_loop_fork(int *arr, char **av, char *envp[], int **array);
pid_t	bonus_child_fork_1(int ac, char **av, char *envp[], int **array);
pid_t	bonus_child_fork_2(int *arr, char **av, char *envp[], int **array);
void	waiting_pid(pid_t f1, pid_t fn, pid_t f2);
pid_t	bonus_child_fork_heredoc_1(char **av, char *envp[], int **pips);
pid_t	bonus_child_fork_heredoc_2(char **av, char *envp[], int **pips);
void	heredoc(int ac, char **av, char *envp[]);
void	bonus_command_exec(char *envp[], char **command, char *x);
void	closing_pipes_herdoc(int **pips);
char	*ft_newstrchr(char *s, char *target);
char	*located_path_return(char *envp[]);
char	*checking_path(char *envp[], char *comm);
void	exec_function(char *envp[], char **command, char *x);
void	pipex_func(char **av, char *envp[], int **pips);
void	closing_pipes(int ac, int **array);
void	checking_ac_length(int ac, char **av);
void	closing_pipes_herdoc(int **pips);
void	protection(int ac);
#endif