#include "../include/minishell.h"

static void	ft_new_pwd(t_minishell *minishell)
{
	char	buffer[PATH_MAX];

	set_env_value("OLDPWD", get_env_value("PWD", minishell), minishell);
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		printf("error\n");
		return ;
	}
	else
	{
		set_env_value("PWD", buffer, minishell);
	}
}

static char	*get_dir(int argc, char **argv, t_minishell *minishell)
{
	char	*dir;

	if (argc == 1)
	{
		dir = get_env_value("HOME", minishell);
	}
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		dir = get_env_value("OLDPWD", minishell);
	}
	dir = argv[1];
	return (dir);
}

void	cd_builtin(int argc, char **argv, t_minishell *minishell)
{
	char	*new_dir;

	if (argc > 2)
		return ;
	new_dir = get_dir(argc, argv, minishell);
	if (chdir(new_dir) == -1)
		return ;
	ft_new_pwd(minishell);
}