#include "../include/minishell.h"

int	get_pipe_outfile(t_minishell *minishell)
{
	if (pipe(minishell->pipe_fd) < 0)
		return ;
	return (minishell->pipe_fd[1]);
}