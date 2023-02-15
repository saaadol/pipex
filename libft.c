#include "pipex.h"
static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_strlen_checker(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_free(char **str, size_t j)
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

static char	*ft_word(char const *s, char c)
{
	size_t	len_word;
	size_t	i;
	char	*word;

	i = 0;
	len_word = ft_strlen_checker(s, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (0);
	while (i < len_word)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	str = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!str)
		return (0);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			str[i] = ft_word(s, c);
			if (!(str[i]))
				return (ft_free(str, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = 0;
	return (str);
}
// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*temp;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	temp = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!temp)
// 		return (0);
// 	while (*s1)
// 		temp[i++] = *s1++;
// 	while (*s2)
// 		temp[i++] = *s2++;
// 	temp[i] = '\0';
// 	return (temp);
// }
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*x1;
	unsigned char	*x2;
	size_t			i;

	x1 = (unsigned char *) s1;
	x2 = (unsigned char *) s2;
	i = 0;
	while (i < n && (x1[i] || x2[i]))
	{
		if (x1[i] != x2[i])
			return (x1[i] - x2[i]);
		i++;
	}
	return (0);
}
char	*ft_join(char *s1, char *s2)
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
	return (s1 = NULL, p);
}