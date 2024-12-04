/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:52:10 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 15:17:36 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

int	is_valid_identifier(const char *str)
{
	if (!str || !(*str) || (*str == '='))
		return (0);
	if (!(ft_isalpha(*str) || *str == '_'))
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!(isalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}

int	validate_input(t_shell *shell, char *new_var)
{
	if (!shell || !shell->env || !new_var)
	{
		ft_putendl_fd("Invalid arguments to add_or_modify_env", STDERR_FILENO);
		shell->last_status = EXIT_FAILURE;
		return (1);
	}
	if (!ft_strchr(new_var, '='))
		return (1);
	return (0);
}

int	modify_existing_env(t_shell *shell, char *new_var, size_t name_len)
{
	size_t	i;
	char	*new_entry;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], new_var, name_len) == 0 && 
			shell->env[i][name_len] == '=')
		{
			new_entry = safe_strdup(new_var);
			if (!new_entry)
			{
				ft_putendl_fd("Memory allocation failed\n", STDERR_FILENO);
				shell->last_status = EXIT_FAILURE;
				return (1);
			}
			safe_free(shell->env[i]);
			shell->env[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (-1);
}

char	**allocate_new_environ(t_shell *shell, size_t env_size)
{
	char	**new_environ;

	new_environ = safe_malloc(sizeof(char *) * (env_size + 2));
	if (!new_environ)
	{
		ft_putendl_fd("Failed memory for new environment", STDERR_FILENO);
		shell->last_status = EXIT_FAILURE;
		return (NULL);
	}
	return (new_environ);
}

int	cp_env(char **new_environ, char **old_env, size_t env_size)
{
	size_t	i;

	i = 0;
	while (i < env_size)
	{
		new_environ[i] = safe_strdup(old_env[i]);
		if (!new_environ[i])
		{
			ft_putendl_fd("Failed to duplicate env variable\n", STDERR_FILENO);
			while (i > 0)
				safe_free(new_environ[--i]);
			safe_free(new_environ);
			return (1);
		}
		i++;
	}
	return (0);
}
