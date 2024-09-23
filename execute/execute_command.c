#include "../include/minishell.h"

int	builtin_check(char **argv)
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

char	*ft_find_command(char **cmd_paths, char *command)
{
	char	*cmd_cpy;
	char	*aux;
	int		i;

	i = 0;
	while ((command[i] == ' ' || command[i] == '\0'))
	{
		if (command[i] == '\0')
			return (NULL);
		i++;
	}
	if (access(command, F_OK | X_OK) == 0)
		return (command);
	while (*cmd_paths)
	{
		aux = ft_strjoin(*cmd_paths, "/");
		cmd_cpy = ft_strjoin(aux, command);
		if (access(cmd_cpy, F_OK | X_OK) == 0)
			return (cmd_cpy);
		free(cmd_cpy);
		cmd_paths++;
	}
	return (NULL);
}

int	cmd_execve(char **cmd_argv, t_minishell *minishell)
{
	char	**cmd_paths;
	char	*command;

	if (get_env_value("PATH", minishell) == NULL)
	{
		execve(cmd_argv[0], cmd_argv, minishell->env);
		return (-1);
	}
	cmd_paths = ft_split(get_env_value("PATH", minishell), ':');
	command = ft_find_command(cmd_paths, cmd_argv[0]);
	if (!command)
	{
		return (-1);
	}
	execve(command, cmd_argv, minishell->env);
	return (1);
}

void	ft_execute_command(t_minishell *minishell, int i, int total_pipes)
{
	char	*cmd;
	char	**cmd_argv;

	cmd = get_cmd_in_line(minishell->tokens, i, total_pipes);
	cmd_argv = ft_split_minishell(cmd);
	pipe_write_dup(minishell, i);
	if (builtin_check(cmd_argv) != 0)
		builtin_execute(minishell, cmd_argv);
	if (cmd_execve(cmd_argv, minishell) < 0)
		return ;
	// close(minishell->infile);
	// close(minishell->outfile);
}