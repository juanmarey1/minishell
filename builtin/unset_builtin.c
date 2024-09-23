#include "../include/minishell.h"

void	unset_builtin(int argc, char **argv, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (argc != 2)
		return ;
	while (ft_strncmp(minishell->env[i], argv[1], ft_strlen(argv[1]) != 0) && minishell->env[i])
		i++;
	if (minishell->env[i] == NULL)
		return ;
	else
		unset_env(argv[1], minishell);
}