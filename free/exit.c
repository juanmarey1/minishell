#include "../include/minishell.h"

void	ft_exit(char *str, t_minishell *minishell)
{
	ft_putendl_fd(str, STDERR_FILENO);
	free_all(minishell);
	exit(minishell->exit_status);
}