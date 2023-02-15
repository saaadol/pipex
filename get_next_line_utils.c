/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:13:18 by souledla          #+#    #+#             */
/*   Updated: 2022/12/21 13:46:41 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)malloc(sizeof (char) * (ft_strlen(s1) + 1));
	if (!temp)
		return (0);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = 0;
	return (free(s1), s1 = NULL, p);
}

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
