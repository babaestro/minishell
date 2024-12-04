/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:09:39 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/03 12:11:54 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

t_heredoc_context	init_heredoc_context(char *input, t_shell *shell)
{
	t_heredoc_context	hd;

	hd.fd = -1;
	hd.line = NULL;
	hd.line_parsed = NULL;
	hd.i = 0;
	hd.input = input;
	hd.shell = shell;
	return (hd);
}

void	cleanup_heredoc_context(t_heredoc_context *ctx)
{
	if (ctx->fd >= 0)
		close(ctx->fd);
	free(ctx->line);
	free(ctx->line_parsed);
}

int	handle_line(t_heredoc_context *hd)
{
	hd->line_parsed = check_dollar(hd->line, hd->shell);
	if (write(hd->fd, hd->line_parsed, ft_strlen(hd->line_parsed)) < 0 || 
		write(hd->fd, "\n", 1) < 0)
	{
		perror("write");
		return (-1);
	}
	free(hd->line_parsed);
	return (0);
}

int	process_single_delimiter(t_heredoc_context *hd)
{
	while (1)
	{
		hd->line = readline("> ");
		if (!hd->line)
		{
			ft_putendl_fd(
				"Warning: heredoc received EOF (Ctrl+D) without delimiter", 
				STDERR_FILENO);
			return (0);
		}
		if (ft_strncmp(hd->line, hd->shell->delimiters[hd->i], 
				ft_strlen(hd->line)) == 0)
		{
			free(hd->line);
			return (0);
		}
		if (handle_line(hd) < 0)
			return (-1);
		free(hd->line);
	}
}

int	process_heredoc_input(t_heredoc_context *hd)
{
	while (hd->i < hd->shell->num_delimiters)
	{
		if (process_single_delimiter(hd) < 0)
		{
			cleanup_heredoc_context(hd);
			return (-1);
		}
		hd->i++;
	}
	return (0);
}
