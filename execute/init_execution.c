#include "../include/minishell.h"

int	init_fork(t_minishell *minishell, int i)
{
	int	status;

	minishell->pid[i] = fork();
	if (minishell->pid[i] < 0)
		return ;
	if (minishell->pid[i] == 0)
		ft_execute_command(minishell, i, minishell->pipes);
	status = ft_set_next_fd(minishell);
	return (status);
}

void	init_execution(t_minishell *minishell)
{
	int	i;

	i = -1;
	if (minishell->pipes > 0)
	{
		minishell->pid = (pid_t *)malloc(sizeof(pid_t) * (minishell->pipes));
		if (!minishell->pid)
			return ;
	}
	while (++i < minishell->pipes + 1)
	{
		minishell->infile = get_infile(minishell, minishell->infile, i);
		minishell->outfile = get_outfile(minishell, minishell->outfile, i);
		if ((i < minishell->pipes) && minishell->outfile == 1)
			minishell->outfile = get_pipe_outfile(minishell);
		minishell->exit_status = init_fork(minishell, i);
		set_new_infile_outfile(minishell);
	}
	close_file_descriptors(minishell);
	free_tokens(minishell);
}