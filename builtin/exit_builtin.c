#include "../include/minishell.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		else
			i++;
	}
	return (1);
}

void	exit_builtin(int argc, char **argv, t_minishell *minishell)
{
	if (argc == 2 && ft_is_num(argv[1]) == 0)
		minishell->exit_status = 255;
	else if (argc == 2 && ft_is_num(argv[1]) == 1)
		minishell->exit_status = ft_atoi(argv[1]);
	else
		printf("too many args\n");
	exit(minishell->exit_status);
}