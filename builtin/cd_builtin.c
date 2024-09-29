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
		return (dir);
	}
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		dir = get_env_value("OLDPWD", minishell);
		return (dir);
	}
	dir = argv[1];
	return (dir);
}

void	cd_builtin(int argc, char **argv, t_minishell *minishell)
{
	char	*new_dir;

	minishell->wait_pid_status = 0;
	if (argc > 2)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (minishell->exit_status = 1, (void)0);
	}
	new_dir = get_dir(argc, argv, minishell);
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(new_dir, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (minishell->exit_status = 1, (void)0);
	}
	ft_new_pwd(minishell);
	minishell->exit_status = 0;
}