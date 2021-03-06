#include "minishell.h"

void	del_ast_expansions(t_AST_expansion *expansions[])
{
	int		i;

	i = -1;
	while (expansions[++i])
	{
		free(expansions[i]->parameter);
		free(expansions[i]);
	}
	free(expansions);
}

void	del_ast_node(t_AST_NODE *node)
{
	if (!node)
		return ;
	free(node->text);
	if (node->expansions)
		del_ast_expansions(node->expansions);
	free(node);
}

void	del_ast_command(t_AST_COMMAND *command)
{
	int	i;

	del_ast_node(command->name);
	i = -1;
	if (command->prefixes)
	{
		while (command->prefixes[++i])
			del_ast_node(command->prefixes[i]);
		free(command->prefixes);
	}
	i = -1;
	if (command->suffixes)
	{
		while (command->suffixes[++i])
			del_ast_node(command->suffixes[i]);
		free(command->suffixes);
	}
	free(command);
}

void	del_ast_commands(t_AST_COMMAND *commands[])
{
	int	i;

	i = -1;
	while (commands[++i])
		del_ast_command(commands[i]);
	free(commands);
}

/*	avoid using it alone!
	should be only called by t_shell methods
*/
void	del_ast_script(t_AST_SCRIPT *script)
{
	del_ast_commands(script->commands);
	free(script);
}
