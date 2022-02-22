#include "minishell.h"

static void	prompt_init(t_prompt *prompt)
{
	rl_catch_signals = 0;
	signal(SIGINT, prompt_new_line);
	signal(SIGQUIT, prompt_ignore_signal);
	prompt->user = getenv("USER");
	prompt->ps1 = new_str_join((char *[]){
			SIGN BGRN EIGN,
			prompt->user, "@minishell > "
			SIGN END EIGN, NULL}, '\0');
	prompt->ps2 = new_str_join((char *[]){
			SIGN BGRN EIGN
			"> "
			SIGN END EIGN, NULL}, '\0');
}

/*
	- prompt: not freed; uses static allocation (init)
	- user: stores result of getenv(); should not be freed
	- ps1, ps2: freed
*/
static void	del_prompt(t_prompt *prompt)
{
	free(prompt->ps1);
	free(prompt->ps2);
}

static void	prompt_run_line(char *line, t_dict *env)
{
	t_token			*tokens;
	t_AST_PIPELINE	*pipeline;

	tokens = lexer(line);
	if (tokens)
	{
		pipeline = parser(tokens, env);
		if (pipeline)
		{
			ast_pipeline_repr(pipeline, 0);
			del_ast_pipeline(pipeline);
		}
	}
	free(line);
}

static void	prompt_loop(t_prompt *prompt, t_dict *env)
{
	char	*line;

	while (true)
	{
		line = readline(prompt->ps1);
		if (is_line_eof(line))
			return (prompt_replace_line_with(line, prompt->ps1, "exit"));
		else if (is_str_equal(line, "exit"))
			return (prompt_exit(line));
		else if (!is_line_empty(line))
		{
			add_history(line);
			prompt_run_line(line, env);
		}
	}
}

void	prompt(t_dict *env)
{
	t_prompt	prompt;

	prompt_init(&prompt);
	prompt_loop(&prompt, env);
	del_prompt(&prompt);
}
