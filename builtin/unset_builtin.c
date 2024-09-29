#include "../include/minishell.h"

static void	unset_loop(int argc, char **argv, t_minishell *minishell)
{
	int	loop_n;
	int	i;

	loop_n = 0;
	while (++loop_n < argc)
	{
		i = 0;
		printf("minishell->env: %s\n", minishell->env[i]);
		printf("argv %s\n", argv[loop_n]);
		while (ft_strncmp(get_env_name(minishell->env[i]), argv[loop_n], ft_strlen(argv[loop_n])) != 0 && minishell->env[i])
			i++;
		printf("env: %s\n", minishell->env[i]);
		if (minishell->env[i] != NULL)
			unset_env(argv[loop_n], minishell);
	}
}

void	unset_builtin(int argc, char **argv, t_minishell *minishell)
{
	int	i;

	i = 0;
	minishell->wait_pid_status = 0;
	if (argc < 2)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		minishell->exit_status = 1;
		return ;
	}
	minishell->exit_status = 0;
	unset_loop(argc, argv, minishell);
}