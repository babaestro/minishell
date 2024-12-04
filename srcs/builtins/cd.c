/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:53:07 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 14:29:00 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

int	cd_error(char *s, t_shell *shell)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd(": no such file or directory", STDERR_FILENO);
	return (shell->last_status = EXIT_FAILURE);
}

void	update_env_variable(t_shell *shell, const char *name, const char *value)
{
	int		i;
	char	*new_var;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = safe_malloc(len);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, name, len);
	ft_strlcat(new_var, "=", len);
	ft_strlcat(new_var, value, len);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0 
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = new_var;
			return ;
		}
		i++;
	}
	shell->env[i] = new_var;
	shell->env[i + 1] = NULL;
}

int	set_new_pwd(t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_variable(shell, "PWD", new_pwd);
		free(new_pwd);
	}
	else
	{
		ft_putendl_fd("cd: error getting new working directory", STDERR_FILENO);
		return (shell->last_status = EXIT_FAILURE);
	}
	return (shell->last_status = EXIT_SUCCESS);
}

char	*set_home(t_shell *shell)
{
	char	*target_dir;

	target_dir = get_env_value("HOME", shell->env);
	if (!target_dir)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		shell->last_status = EXIT_FAILURE;
		return (target_dir);
	}
	return (target_dir);
}

int	cd_builtin(int nr_args, t_command *command, t_shell *shell)
{
	char	*target_dir;

	target_dir = NULL;
	if (shell->path == 1)
		return (shell->last_status = EXIT_FAILURE);
	if (nr_args == 1 || (nr_args == 2 && 
			ft_strncmp(command->args[1], "~", 2) == 0))
	{
		target_dir = set_home(shell);
		if (!target_dir)
			return (shell->last_status);
	}
	else if (nr_args == 2)
		target_dir = command->args[1];
	else
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (shell->last_status = EXIT_FAILURE);
	}
	if (chdir(target_dir) != 0)
	{
		return (cd_error(target_dir, shell));
	}
	set_new_pwd(shell);
	return (shell->last_status = EXIT_SUCCESS);
}
