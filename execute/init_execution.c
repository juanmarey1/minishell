#include "../include/minishell.h"

void	ft_set_next_fd(t_minishell *minishell, int i)
{
	if (i < minishell->pipes && minishell->pipes != 0)
	{
		if (minishell->outfile == minishell->pipe_fd[i][1])
		{
			if (minishell->infile != 0)
				close(minishell->infile);
			minishell->infile = minishell->pipe_fd[i][0];
		}
		else
			close(minishell->pipe_fd[i - 1][0]);
		close(minishell->outfile);
		minishell->outfile = STDOUT_FILENO;
	}
	if (i == minishell->pipes && minishell->pipes != 0)
	{
		close(minishell->infile);
		minishell->infile = 0;
	}
}

void	init_fork(t_minishell *minishell, int i)
{
	minishell->pid[i] = fork();
	if (minishell->pid[i] < 0)
		return ;
	if (minishell->pid[i] == 0)
		ft_execute_command(minishell, i, minishell->pipes);
	ft_set_next_fd(minishell, i);
}

void	create_forks(t_minishell *minishell)
{
	if (minishell->pipes >= 0)
	{
		minishell->pid = (pid_t *)malloc(sizeof(pid_t) * (minishell->pipes + 1));
		if (!minishell->pid)
			return ;
	}
	else
		return ;
}

void	init_execution(t_minishell *minishell)
{
	int	i;

	i = 0;
	create_forks(minishell);
	create_pipes(minishell);
	while (i < minishell->pipes + 1)
	{
		minishell->infile = get_infile(minishell, minishell->infile, i);
		if (i < minishell->pipes)
			pipe_create(minishell, i);
		if (i < minishell->pipes)
			minishell->outfile = minishell->pipe_fd[i][1];
		minishell->outfile = get_outfile(minishell, minishell->outfile, i);
		printf("infile: %d\noutfile: %d\ni: %d\n", minishell->infile, minishell->outfile, i);
		init_fork(minishell, i);
		i++;
	}
	close_file_descriptors(minishell);
	free_tokens(minishell);
}