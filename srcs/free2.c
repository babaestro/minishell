/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:33:42 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/02 15:22:26 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr != NULL)
		track_allocation(ptr);
	return (ptr);
}

void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		safe_free(cmd->cmd);
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				safe_free(cmd->args[i]);
				i++;
			}
			safe_free(cmd->args);
		}
		safe_free(cmd->input_file);
		safe_free(cmd->output_file);
		safe_free(cmd->cmd_path);
		free_command(cmd->next);
		safe_free(cmd);
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell)
	{
		if (shell->env)
		{
			while (shell->env[i])
			{
				safe_free(shell->env[i]);
				i++;
			}
			safe_free(shell->env);
		}
		free_command(shell->commands);
		safe_free(shell);
	}
}

void	cleanup_command(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	cleanup_redirections(cmd->redirections);
	cmd->redirections = NULL;
	safe_free(cmd->cmd);
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			safe_free(cmd->args[i]);
			i++;
		}
		safe_free(cmd->args);
	}
	safe_free(cmd->cmd_path);
	safe_free(cmd->input_file);
	safe_free(cmd->output_file);
	cmd->arg_count = 0;
	safe_free(cmd);
}
