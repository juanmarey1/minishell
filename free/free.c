#include "../include/minishell.h"

void	free_all(t_minishell *minishell)
{
	if (minishell->env)
		ft_free_double_array(minishell->env);
	return ;
}