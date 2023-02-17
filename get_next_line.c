/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:58:37 by souledla          #+#    #+#             */
/*   Updated: 2023/02/17 01:01:24 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	isnew(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*findline(int fd, char *str)
{
	char	*stash;
	int		re;

	re = 1;
	stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (free(str), NULL);
	while (re && !ft_strchr(str, '\n'))
	{
		re = read(fd, stash, BUFFER_SIZE);
		if (re < 0)
		{
			free(stash);
			free(str);
			str = NULL;
			return (NULL);
		}
		stash[re] = '\0';
		str = ft_strjoin(str, stash);
	}
	return (free(stash), str);
}

char	*newline(char *str)
{
	char	*stash;
	int		i;
	int		len;

	i = 0;
	if (!str[i])
		return (NULL);
	len = isnew(str);
	stash = malloc(sizeof(char) * (len + 1));
	if (!stash)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		stash[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		stash[i++] = '\n';
	stash[i] = '\0';
	return (stash);
}

char	*afterline(char *str)
{
	char	*stash;
	int		i;
	int		j;
	int		len;

	j = isnew(str);
	if (j == ft_strlen(str))
		return (free(str), NULL);
	i = 0;
	len = ft_strlen(str) - j + 1;
	stash = malloc(sizeof(char) * len);
	if (!stash)
		return (NULL);
	while (str[j])
		stash[i++] = str[j++];
	stash[i] = '\0';
	return (free(str), str = NULL, stash);
}

char	*get_next_line(int fd)
{
	static char		*x;
	char			*y;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!x)
		x = ft_strdup("");
	if (!x)
		return (0);
	x = findline(fd, x);
	if (!x)
		return (NULL);
	y = newline(x);
	x = afterline(x);
	return (y);
}
// int main()
// {
// 	int fd;
// 	fd = open("test.txt", O_RDONLY);
// 	char *s;
// 	s = get_next_line(fd);
// 	s = get_next_line(fd);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// }