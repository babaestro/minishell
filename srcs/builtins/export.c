/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:31:54 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 15:17:21 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

static int	add_new_var(char **new_environ, char *new_var, size_t env_size)
{
	new_environ[env_size] = safe_strdup(new_var);
	if (!new_environ[env_size])
	{
		ft_putendl_fd("Failed to duplicate new variable", STDERR_FILENO);
		while (env_size > 0)
			safe_free(new_environ[--env_size]);
		safe_free(new_environ);
		return (1);
	}
	new_environ[env_size + 1] = NULL;
	return (0);
}

static void	cleanup_old_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env[i])
		safe_free(shell->env[i++]);
	safe_free(shell->env);
}

static int	add_or_modify_env(t_shell *shell, char *new_var)
{
	size_t	n_l;
	size_t	e_s;
	char	**n_e;
	int		modify_result;

	if (validate_input(shell, new_var))
		return (1);
	n_l = ft_strchr(new_var, '=') - new_var;
	modify_result = modify_existing_env(shell, new_var, n_l);
	if (modify_result != -1)
		return (modify_result);
	e_s = 0;
	while (shell->env[e_s])
		e_s++;
	n_e = allocate_new_environ(shell, e_s);
	if (cp_env(n_e, shell->env, e_s) || add_new_var(n_e, new_var, e_s))
	{
		shell->last_status = EXIT_FAILURE;
		return (1);
	}
	cleanup_old_env(shell);
	shell->env = n_e;
	shell->last_status = EXIT_SUCCESS;
	return (0);
}

int	export_identify(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putendl_fd("export: not a valid identifier", STDERR_FILENO);
			shell->last_status = EXIT_FAILURE;
			return (1);
		}
		if (add_or_modify_env(shell, args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	export_builtin(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell || !args)
	{
		ft_putendl_fd("Invalid arguments to export_builtin\n", STDERR_FILENO);
		shell->last_status = EXIT_FAILURE;
		return (1);
	}
	if (!args[0])
	{
		while (shell->env && shell->env[i])
		{
			printf("export %s\n", shell->env[i]);
			i++;
		}
		return (0);
	}
	export_identify(args, shell);
	shell->last_status = EXIT_SUCCESS;
	return (0);
}
