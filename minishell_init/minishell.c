#include "../include/minishell.h"

void	init_minishell(t_minishell *minishell, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	minishell->exit = 0;
	minishell->exit_status = 0;
	minishell->user_input = NULL;
	minishell->tokens = NULL;
	minishell->pipes = 0;
	minishell->error = 0;
	minishell->infile = 0;
	minishell->outfile = 1;
	minishell->pipe_fd[0] = -1;
	minishell->pipe_fd[1] = -1;
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	minishell;

	init_minishell(&minishell, argc, argv);
	get_list_of_env(env, &minishell);
	sum_one_to_shlvl(&minishell);
	while (minishell.exit == 0)
	{
		minishell.user_input = init_input(&minishell);
		if (minishell.user_input == NULL)
		{
			break ;
		}
		input_to_tokens(&minishell);
		free(minishell.user_input);
		execute_commands(&minishell);
	}
	rl_clear_history();
	free_all(&minishell);
	return (0);
}