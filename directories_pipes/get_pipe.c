#include "../include/minishell.h"

void	pipe_write_dup(t_minishell *minishell, int i)
{
	if (i != 0)
	{
		if (minishell->infile == minishell->pipe_fd[i - 1][0])
		{
			dup2(minishell->infile, STDIN_FILENO);
			close(minishell->pipe_fd[i - 1][1]);
			close(minishell->pipe_fd[i - 1][0]);
		}
	}
	else
		dup2(minishell->infile, STDIN_FILENO);
	if (minishell->pipes != 0 && i < minishell->pipes)
	{
		if (minishell->outfile == minishell->pipe_fd[i][1])
		{
			dup2(minishell->outfile, STDOUT_FILENO);
			close(minishell->pipe_fd[i][0]);
			close(minishell->pipe_fd[i][1]);
		}
	}
	else
		dup2(minishell->outfile, STDOUT_FILENO);
}

void	pipe_create(t_minishell *minishell, int i)
{
	if (pipe(minishell->pipe_fd[i]) < 0)
		return ;
	printf("pipe-read: %d\n", minishell->pipe_fd[i][0]);
	printf("pipe-write: %d\n", minishell->pipe_fd[i][1]);
}

void	create_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->pipes > 0)
	{
		minishell->pipe_fd = (int **)malloc(sizeof(int *) * minishell->pipes);
		if (!minishell->pipe_fd)
			return ;
		while (i < minishell->pipes)
		{
			minishell->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
			if (!minishell->pipe_fd[i])
				return ;
			minishell->pipe_fd[i][0] = -1;
			minishell->pipe_fd[i][1] = -1;
			i++;
		}
	}
}