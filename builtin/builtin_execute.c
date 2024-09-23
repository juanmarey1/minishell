#include "../include/minishell.h"

void	builtin_execute(t_minishell *minishell, char **cmd_argv)
{
	if	(ft_strncmp(cmd_argv[0], ECHO, ft_strlen(ECHO)))
		echo_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], PWD, ft_strlen(PWD)))
		pwd_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], CD, ft_strlen(CD)))
		cd_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], EXPORT, ft_strlen(EXPORT)))
		export_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], UNSET, ft_strlen(UNSET)))
		unset_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], EXIT, ft_strlen(EXIT)))
		exit_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else if (ft_strncmp(cmd_argv[0], ENV, ft_strlen(ENV)))
		env_builtin(double_str_len(cmd_argv), cmd_argv, minishell);
	else
		return ;
}