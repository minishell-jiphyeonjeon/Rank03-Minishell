#include "minishell.h"

t_res	error_msg_return(char *message[])
{
	const int	len = ft_arr_len(message);
	int			i;

	i = -1;
	while (++i < len)
		ft_write(STDERR_FILENO, message[i]);
	return (ERR);
}

t_res	error_malloc_msg(void)
{
	return (error_msg_return(
			(char *[]){BRED, MINISHELL, MALLOC_ERROR, END, NULL}));
}

t_res	error_with_exitcode(char *message[], t_dict *env, int exitcode)
{
	env_set_exitcode(env, exitcode);
	return (error_msg_return(message));
}

t_res	error_msg_bad_opt(char *category, char *opt)
{
	if (!is_opt(opt))
		return (ERR);
	ft_writes(STDERR_FILENO, (char *[]){
		BHRED, category, ": bad option: -", NULL});
	write(STDERR_FILENO, &opt[1], 1);
	ft_write(STDERR_FILENO, END "\n");
	return (ERR);
}
