#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (ERR);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	is_str_equal(const char *str1, const char *str2)
{
	const int	str1_len = ft_strlen(str1);
	const int	str2_len = ft_strlen(str2);
	int			i;

	if (!str1 || !str2 || str1_len != str2_len)
		return (false);
	i = -1;
	while (++i < str1_len)
		if (str1[i] != str2[i])
			return (false);
	return (true);
}