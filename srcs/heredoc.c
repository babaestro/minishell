/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:02:01 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/03 12:10:36 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

// t_heredoc_context	init_heredoc_context(char *input, t_shell *shell)
// {
// 	t_heredoc_context	hd;

// 	hd.fd = -1;
// 	hd.line = NULL;
// 	hd.line_parsed = NULL;
// 	hd.i = 0;
// 	hd.input = input;
// 	hd.shell = shell;
// 	return (hd);
// }

// void	cleanup_heredoc_context(t_heredoc_context *ctx)
// {
// 	if (ctx->fd >= 0)
// 		close(ctx->fd);
// 	free(ctx->line);
// 	free(ctx->line_parsed);
// }

// static int	handle_line(t_heredoc_context *hd)
// {
// 	hd->line_parsed = check_dollar(hd->line, hd->shell);
// 	if (write(hd->fd, hd->line_parsed, ft_strlen(hd->line_parsed)) < 0 || 
// 		write(hd->fd, "\n", 1) < 0)
// 	{
// 		perror("write");
// 		return (-1);
// 	}
// 	free(hd->line_parsed);
// 	return (0);
// }

// static int	process_single_delimiter(t_heredoc_context *hd)
// {
// 	while (1)
// 	{
// 		hd->line = readline("> ");
// 		if (!hd->line)
// 		{
// 			ft_putendl_fd(
// 				"Warning: heredoc received EOF (Ctrl+D) without delimiter", 
// 				STDERR_FILENO);
// 			return (0);
// 		}
// 		if (ft_strncmp(hd->line, hd->shell->delimiters[hd->i], 
// 				ft_strlen(hd->line)) == 0)
// 		{
// 			free(hd->line);
// 			return (0);
// 		}
// 		if (handle_line(hd) < 0)
// 			return (-1);
// 		free(hd->line);
// 	}
// }

// int	process_heredoc_input(t_heredoc_context *hd)
// {
// 	while (hd->i < hd->shell->num_delimiters)
// 	{
// 		if (process_single_delimiter(hd) < 0)
// 		{
// 			cleanup_heredoc_context(hd);
// 			return (-1);
// 		}
// 		hd->i++;
// 	}
// 	return (0);
// }

int	set_heredoc(char *input, t_shell *shell)
{
	t_heredoc_context	hd;

	hd = init_heredoc_context(input, shell);
	get_delimiter(input, shell);
	if (hd.shell->num_delimiters <= 0)
		return (-1);
	hd.fd = open("temporary.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (hd.fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (process_heredoc_input(&hd) < 0)
		return (-1);
	close(hd.fd);
	return (open("temporary.tmp", O_RDONLY));
}

void	handle_heredoc_child_process(int heredoc_fd, 
		char *input, t_shell *shell)
{
	char	*command_part;

	if (dup2(heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(heredoc_fd);
		exit(EXIT_FAILURE);
	}
	close(heredoc_fd);
	command_part = copy_until_char(input, '<');
	if (command_part)
	{
		handle_single_command(command_part, shell);
		free(command_part);
	}
	exit(shell->last_status);
}

void	handle_heredoc_parent_process(int heredoc_fd, pid_t pid, t_shell *shell)
{
	int	status;

	close(heredoc_fd);
	waitpid(pid, &status, 0);
	shell->last_status = WEXITSTATUS(status);
}

int	set_heredoc_alone(char *input, t_shell *shell)
{
	int		heredoc_fd;
	pid_t	pid;

	heredoc_fd = set_heredoc(input, shell);
	if (heredoc_fd < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(heredoc_fd);
		return (-1);
	}
	else if (pid == 0)
		handle_heredoc_child_process(heredoc_fd, input, shell);
	else
		handle_heredoc_parent_process(heredoc_fd, pid, shell);
	if (unlink("temporary.tmp") != 0)
		perror("unlink");
	return (0);
}
