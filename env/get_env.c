#include "../include/minishell.h"

char	**new_list_of_env(char **environ, t_minishell *minishell)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (minishell->size_of_env + 1));
	if (!new_env)
		ft_exit(MALLOC_ERR, minishell);
	while (i < minishell->size_of_env)
	{
		if (!(new_env[i] = ft_strdup(environ[i])))
			ft_exit(MALLOC_ERR, minishell);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	get_list_of_env(char **environ, t_minishell *minishell)
{
	minishell->size_of_env = double_str_len(environ);
	minishell->env = new_list_of_env(environ, minishell);
}