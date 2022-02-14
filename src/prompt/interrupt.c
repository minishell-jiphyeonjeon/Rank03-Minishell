#include "minishell.h"

void	prompt_ignore_signal(int status)
{
	(void)status;
}

/*
	- printf: move to new line
	- rl_on_new_line: Regenerate the prompt on a newline
	- rl_replace_line: Clear the previous text
*/
void	prompt_new_line(int status)
{
	(void)status;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}