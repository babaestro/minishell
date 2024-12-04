/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:18:26 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 15:30:16 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

int	count_args(t_token *tokens)
{
	t_token	*current;
	int		arg_count;

	current = tokens;
	arg_count = 0;
	while (current && current->type != TOKEN_PIPE)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	free_part_command(t_token *current, t_command *cmd)
{
	if (current->next && current->next->type == TOKEN_WORD)
	{
		safe_free(cmd->output_file);
		cmd->output_file = safe_strdup(current->next->value);
		if (!cmd->output_file)
			return ;
		current = current->next;
	}
}

static void	save_commands(t_token *current, t_command *cmd)
{
	int	i;

	i = 0;
	while (current && current->type != TOKEN_PIPE && i < MAX_ARGS - 1)
	{
		if (current->type == TOKEN_REDIRECT_OUT || 
			current->type == TOKEN_REDIRECT_APPEND)
			free_part_command(current, cmd);
		if (i == 0)
			cmd->cmd = safe_strdup(current->value);
		if (!cmd->args)
			cmd->args = safe_malloc(sizeof(char *) * MAX_ARGS);
		if (!cmd->cmd || !cmd->args)
			return ;
		cmd->args[i] = safe_strdup(current->value);
		if (!cmd->args[i])
			return ;
		i++;
		current = current->next;
	}
	cmd->args[i] = NULL;
	cmd->arg_count = i;
}

t_command	*create_commands(t_token *tokens, t_shell *shell)
{
	t_command	*cmd;
	int			arg_count;
	t_token		*current;

	cmd = safe_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	arg_count = count_args(tokens);
	cmd->args = safe_malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		safe_free(cmd);
		return (NULL);
	}
	current = tokens;
	save_commands(current, cmd);
	cmd->cmd_path = find_command(cmd, shell);
	return (cmd);
}

void	execute_command(t_command *cmd, t_shell *shell, t_token *token)
{
	int		flag;

	if (!shell->env || !cmd)
		return ;
	flag = exec_builtin(cmd, shell, token);
	if (flag == 0)
		exec_external(cmd, shell);
	if (cmd->old_in != -1)
	{
		dup2(cmd->old_in, STDIN_FILENO);
		cmd->old_in = -1;
	}
	if (cmd->old_out != -1)
	{
		dup2(cmd->old_out, STDOUT_FILENO);
		cmd->old_out = -1;
	}
}
