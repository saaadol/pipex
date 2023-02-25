/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souledla <souledla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:38:20 by souledla          #+#    #+#             */
/*   Updated: 2023/02/24 15:22:49 by souledla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	counting_words(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (counter);
}

static size_t	checking_strlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**freeing_memory(char **str, size_t j)
{
	int	i;

	i = j;
	while (i >= 0)
	{
		if (i == 0)
		{
			free(str[i]);
			str[i] = 0;
			break ;
		}
		free(str[i]);
		str[i] = 0;
		i--;
	}
	free(str);
	str = 0;
	return (0);
}

static char	*returning_word(char const *s, char c)
{
	size_t	word_len;
	size_t	i;
	char	*word_;

	i = 0;
	word_len = checking_strlen(s, c);
	word_ = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word_)
		return (0);
	while (i < word_len)
	{
		word_[i] = s[i];
		i++;
	}
	word_[i] = '\0';
	return (word_);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	array = (char **)malloc(sizeof(char *) * (counting_words(s, c) + 1));
	if (!array)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			array[i] = returning_word(s, c);
			if (!(array[i]))
				return (freeing_memory(array, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	array[i] = 0;
	return (array);
}
