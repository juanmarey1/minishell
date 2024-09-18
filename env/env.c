#include "../include/minishell.h"

void	set_env_value(char *str, char *value, t_minishell *minishell)
{
	int		i;
	char	*str_cpy;

	i = 0;
	while (minishell->env[i] && ft_strncmp(minishell->env[i], str, ft_strlen(str)))
		i++;
	if (minishell->env[i] == NULL)
		return ;
	else
	{
		free(minishell->env[i]);
		str_cpy = ft_strjoin(ft_strdup(str), "=");
		minishell->env[i] = ft_strjoin(str_cpy, value);
	}
	return ;
}

char	*get_env_value(char *str, t_minishell *minishell)
{
	int		i;
	char	*value;

	i = 0;
	while (minishell->env[i] && ft_strncmp(minishell->env[i], str, ft_strlen(str)))
		i++;
	if (minishell->env[i] == NULL)
		return (NULL);
	else
	{
		value = minishell->env[i];
		while (*value != '=')
			value++;
		value++;
	}
	return (value);
}

void	sum_one_to_shlvl(t_minishell *minishell)
{
	char	*shlvl;
	int		shlvl_num;
	char	*shlvl_num_array;

	shlvl = get_env_value("SHLVL", minishell);
	shlvl_num = ft_atoi(shlvl) + 1;
	shlvl_num_array = ft_itoa(shlvl_num);
	set_env_value("SHLVL", shlvl_num_array, minishell);
	free(shlvl_num_array);
}