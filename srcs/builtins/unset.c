/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:02:36 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/26 16:56:44 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

static int	find_env_var(t_shell *shell, const char *var_name)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], var_name, name_len) == 0 && 
			(shell->env[i][name_len] == '=' || shell->env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_and_shift_env(t_shell *shell, int index)
{
	safe_free(shell->env[index]);
	while (shell->env[index] != NULL)
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
}

int	unset_env_var(t_shell *shell, char *var_name)
{
	int	var_index;

	var_index = find_env_var(shell, var_name);
	if (var_index >= 0)
	{
		remove_and_shift_env(shell, var_index);
		return (0);
	}
	return (1);
}

int	unset_builtin(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (!args[0])
		return (1);
	while (args[i])
	{
		unset_env_var(shell, args[i]);
		i++;
	}
	shell->last_status = EXIT_SUCCESS;
	return (0);
}
