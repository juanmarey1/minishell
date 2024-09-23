#include "../include/minishell.h"

static int	has_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_env_name(char *str)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

void	export_builtin(int argc, char **argv, t_minishell *minishell)
{
	int		i;
	char	*env_name;

	i = 0;
	if (argc == 1)
	{
		while (minishell->env[i])
		{
			env_name = get_env_name(minishell->env[i]);
			printf("declare -x %s=\"%s\"", env_name, get_env_value(env_name, minishell));
			free(env_name);
			i++;
		}
	}
	else
	{
		if (has_equal_sign(argv[1]) == 0)
			return ;
		add_env(argv[1], minishell);
	}
}