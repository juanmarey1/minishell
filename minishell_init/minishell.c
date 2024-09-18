#include "../include/minishell.h"

void	init_minishell(t_minishell *minishell)
{
	minishell->exit = 0;
	minishell->exit_status = 0;
	minishell->user_input = NULL;
	minishell->tokens = NULL;
	minishell->pipes = 0;
	minishell->error = 0;
}

char **mini_env = NULL;

int	main(void)
{
	t_minishell	minishell;

	init_minishell(&minishell);
	get_list_of_env(mini_env, &minishell);
	sum_one_to_shlvl(&minishell);
	while (minishell.exit == 0)
	{
		minishell.user_input = init_input(&minishell);
		if (minishell.user_input == NULL)
		{
			break ;
		}
		input_to_tokens(&minishell);
	}
	
	// TEST FOR ENV //
	env_test(&minishell);

	free_all(&minishell);

	return (0);
}