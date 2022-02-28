#include "minishell.h"

bool	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_quotechar(char c)
{
	if (c == '\"' || c == '\'')
		return (true);
	return (false);
}
