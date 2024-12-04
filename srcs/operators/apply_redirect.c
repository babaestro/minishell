/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:04:55 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/02 14:06:09 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_multiple_redirections(t_command *cmd, t_shell *shell)
{
	t_redirection	*current;
	int				fd_in;
	int				fd_out;

	current = cmd->redirections;
	fd_in = -1;
	fd_out = -1;
	while (current)
	{
		if (current->type == TOKEN_REDIRECT_IN)
			fd_in = multiple_in(current, fd_in, shell);
		else if (current->type == TOKEN_REDIRECT_OUT)
			fd_out = multiple_out(current, fd_out, shell);
		else if (current->type == TOKEN_REDIRECT_APPEND)
			fd_out = multiple_append(current, fd_out, shell);
		current = current->next;
	}
	close_multiple(cmd, fd_in, fd_out);
	ft_correctargs(cmd);
	return (0);
}

int	apply_redirections(t_command *cmd, t_shell *shell)
{
	t_redirection	*current;
	int				status;

	current = cmd->redirections;
	status = 0;
	while (current)
	{
		if (current->type == TOKEN_REDIRECT_IN)
			status = redirect_input(cmd, current->filename, shell);
		else if (current->type == TOKEN_REDIRECT_APPEND)
			status = redirect_append(cmd, current->filename);
		else if (current->type == TOKEN_REDIRECT_OUT)
			status = redirect_output(cmd, current->filename);
		if (status == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

void	cleanup_redirections(t_redirection *redirections)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
}

int	apply_other_redirections(t_command *cmd, t_shell *shell)
{
	if (has_multiple_redirections(cmd))
		return (apply_multiple_redirections(cmd, shell));
	else
		return (apply_redirections(cmd, shell));
}
