/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:45:07 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/04 15:50:04 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

int	redirect_operators(t_token *token, t_command *cmd, t_shell *shell)
{
	if (parse_redirections(token, cmd) != 0)
		return (-1);
	return (apply_other_redirections(cmd, shell));
}

int parse_redirections(t_token *token, t_command *cmd)
{
    t_redirection *last_redir = NULL;
    t_redirection *new_redir;

    while (token != NULL)
    {
        if (token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_REDIRECT_APPEND)
        {
            if (token->next == NULL)
                return (-1);
            new_redir = malloc(sizeof(t_redirection));
            if (!new_redir)
                return (-1);
            new_redir->type = token->type;
            new_redir->filename = ft_strdup(token->next->value);
            new_redir->next = NULL;
            if (last_redir)
                last_redir->next = new_redir;
            else
                cmd->redirections = new_redir;
            last_redir = new_redir;
            token = token->next;
        }
        token = token->next;
    }
    return (0);
}


int	redirect_input(t_command *cmd, char *filename, t_shell *shell)
{
	cmd->input_file = filename;
	cmd->new_in = open(filename, O_RDONLY);
	if (cmd->new_in == -1)
	{
		shell->last_status = 1;
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (-1);
	}
	cmd->old_in = dup(STDIN_FILENO);
	if (dup2(cmd->new_in, STDIN_FILENO) == -1)
	{
		close(cmd->new_in);
		return (-1);
	}
	close(cmd->new_in);
	ft_correctargs(cmd);
	return (0);
}

int	redirect_output(t_command *cmd, char *filename)
{
	cmd->output_file = filename;
	cmd->append_output = 0;
	cmd->new_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->new_out == -1)
		return (-1);
	cmd->old_out = dup(STDOUT_FILENO);
	if (dup2(cmd->new_out, STDOUT_FILENO) == -1)
	{
		close(cmd->new_out);
		return (-1);
	}
	close(cmd->new_out);
	ft_correctargs(cmd);
	return (0);
}

int	redirect_append(t_command *cmd, char *filename)
{
	cmd->output_file = filename;
	cmd->append_output = 1;
	cmd->new_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->new_out == -1)
		return (-1);
	cmd->old_out = dup(STDOUT_FILENO);
	if (dup2(cmd->new_out, STDOUT_FILENO) == -1)
	{
		close(cmd->new_out);
		return (-1);
	}
	close(cmd->new_out);
	ft_correctargs(cmd);
	return (0);
}
