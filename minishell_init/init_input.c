#include "../include/minishell.h"

char	*init_input(t_minishell *minishell)
{
	char	*input;

	if (get_env_value("PS1", minishell) == NULL)
		set_env_value("PS1", "$> ", minishell);
	if (isatty(STDIN_FILENO))
		input = readline(get_env_value("PS1", minishell));
	else
		input = NULL;
	if (input == NULL)
		return (NULL);
	if (isatty(STDIN_FILENO) && (input != NULL && input[0] != '\0'))
		add_history(input);
	return (input);
}