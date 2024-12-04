/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:26:08 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/20 16:55:15 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

t_shell	*initialize_shell(char **envp)
{
	t_shell	*shell;

	shell = safe_malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = copy_env(envp);
	if (!shell->env)
	{
		safe_free(shell);
		return (NULL);
	}
	shell->commands = NULL;
	shell->full_input = 0;
	shell->cmd_count = 0;
	shell->last_status = 0;
	shell->path = 0;
	shell ->pipe_count = 0;
	shell->delimiters = NULL;
	shell->num_delimiters = 0;
	return (shell);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

void	set_env(int count, char **new_env, char **envp)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		len = ft_strlen((const char *)envp[i]);
		new_env[i] = safe_malloc(len + 1);
		if (!new_env[i])
		{
			safe_free(new_env);
			return ;
		}
		j = 0;
		while (j < len)
		{
			new_env[i][j] = envp[i][j];
			j++;
		}
		new_env[i][j] = '\0';
		i++;
	}
	new_env[count] = NULL;
}

char	**copy_env(char **envp)
{
	int		count;
	char	**new_env;

	count = count_env_vars(envp);
	new_env = safe_malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	set_env(count, new_env, envp);
	return (new_env);
}
