#include "../include/minishell.h"

void	env_builtin(int argc, char **argv, t_minishell *minishell)
{
	int	i;

	i = 0;
	(void)argv;
	if (!minishell->env)
		return ;
	if (argc != 1)
		return ;
	else
	{
		while (minishell->env[i])
		{
			printf("%s\n", minishell->env[i]);
			i++;
		}
	}
	return ;
}