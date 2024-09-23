#include "../include/minishell.h"

void	close_file_descriptors(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 0;
	while (i < minishell->pipes)
	{
		if (minishell->pipe_fd[i][1] < 0)
			close(minishell->pipe_fd[i][1]);
		if (minishell->pipe_fd[i][0] < 0)
			close(minishell->pipe_fd[i][0]);
		free(minishell->pipe_fd[i]);
		i++;
		
	}
	i = -1;
	while (++i < minishell->pipes + 1)
		waitpid(minishell->pid[i], &status, 0);
	minishell->pipes = 0;
	minishell->pid = 0;
	minishell->infile = 0;
	minishell->outfile = 0;
	free(minishell->pipe_fd);
	minishell->exit_status = status;
}