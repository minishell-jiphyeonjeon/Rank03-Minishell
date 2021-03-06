#include "libft.h"

static int	count_words(char const *str, char delimiter)
{
	int		i;
	int		count;
	bool	prev_delim;

	i = -1;
	count = 1;
	prev_delim = false;
	while (str[++i])
	{
		if (str[i] == delimiter)
			prev_delim = true;
		else if (prev_delim)
		{
			prev_delim = false;
			count++;
		}
	}
	return (count);
}

static int	wordlen(int i, char const *str, char const delimiter)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != delimiter)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**write_words(
	char **arr, int words, char const *str, char delimitor)
{
	int	i;
	int	j;
	int	word_idx;

	i = 0;
	word_idx = -1;
	while (++word_idx < words)
	{
		while (str[i] == delimitor)
			i++;
		arr[word_idx] = ft_calloc(sizeof(char), wordlen(i, str, delimitor));
		if (!arr[word_idx])
		{
			del_arr(arr);
			return (NULL);
		}
		j = 0;
		while (str[i] && str[i] != delimitor)
			arr[word_idx][j++] = str[i++];
	}
	return (arr);
}

char	**new_str_split(char const *str, char delimitor)
{
	char	**strarr;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(str, delimitor);
	strarr = ft_calloc(sizeof(char *), words);
	if (!strarr)
		return (NULL);
	return (write_words(strarr, words, str, delimitor));
}
