#include "../include/minishell.h"

char	*builtin_check(char **argv)
{
	if (ft_strncmp(argv[0], ECHO, ft_strlen(ECHO)) &&
		ft_strncmp(argv[0], PWD, ft_strlen(PWD)) &&
		ft_strncmp(argv[0], CD, ft_strlen(CD)) &&
		ft_strncmp(argv[0], EXPORT, ft_strlen(EXPORT)) &&
		ft_strncmp(argv[0], UNSET, ft_strlen(UNSET)) &&
		ft_strncmp(argv[0], EXIT, ft_strlen(EXIT)) &&
		ft_strncmp(argv[0], ENV, ft_strlen(ENV)))
		return (0);
	else	
		return (1);
}

char	*get_cmd_in_line(t_token **tokens, int i, int total_pipes)
{
	t_token *list;

	list = *tokens;
	while ((total_pipes) - i < total_pipes)
	{
		while (list && list->type != PIPE)
			list = list->next;
		list = list->next;
		i--;
	}
	while (list && list->type != PIPE)
	{
		if (list->cmd == 1)
			return (list->str);
		else
			list = list->next;
	}
	return (NULL);
}

void	ft_execute_command(t_minishell *minishell, int i, int total_pipes)
{
	char	*cmd;
	char	**cmd_argv;

	cmd = get_cmd_in_line(minishell->tokens, i, total_pipes);
	cmd_argv = ft_split_minishell(cmd);
	dup2(minishell->infile, STDIN_FILENO);
	dup2(minishell->outfile, STDOUT_FILENO);
	if (minishell->pipe_fd[0] >= 0 && minishell->pipe_fd[0] >= 0)
	{
		close(minishell->pipe_fd[0]);
		close(minishell->pipe_fd[1]);
	}
	if (builtin_check(cmd_argv) != 0)
		builtin_execute(minishell, cmd_argv);
}