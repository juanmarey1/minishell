#include "../include/minishell.h"

void	pwd_builtin(int argc, char **argv)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		printf("error\n");
	}
	else
		ft_putendl_fd(buffer, STDOUT_FILENO);
}