/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:41:08 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/03 15:41:20 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "memory.h"

// int	is_inside_quotes(const char *str, const char *substr)
// {
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	while (*str)
// 	{
// 		if (*str == '\'' && !in_double_quotes)
// 			in_single_quotes = !in_single_quotes;
// 		else if (*str == '"' && !in_single_quotes)
// 			in_double_quotes = !in_double_quotes;
// 		else if (str == substr && !in_single_quotes && !in_double_quotes)
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

int	process_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*commands;
	t_token		*current;

	current = tokens;
	commands = create_commands(tokens, shell);
	if (!commands)
	{
		printf ("Failed to create commands\n");
		return (-1);
	}
	check_operators(current);
	redirect_operators(current, commands, shell);
	commands->new_in = -1;
	commands->new_out = -1;
	execute_command(commands, shell, tokens);
	cleanup_command(commands);
	return (0);
}

void	handle_single_command(char *command, t_shell *shell)
{
	char	*parsed_command;
	t_token	*tokens;

	parsed_command = check_dollar(command, shell);
	if (!parsed_command || *parsed_command == '\0')
	{
		free(parsed_command);
		return ;
	}
	tokens = tokenize(parsed_command);
	if (!tokens)
	{
		free(parsed_command);
		return ;
	}
	process_tokens(tokens, shell);
	free_tokens(tokens);
	if (parsed_command != command)
		free(parsed_command);
}

void	handle_no_pipe(char **commands, t_shell *shell)
{
	if (ft_strnstr(commands[0], "<<", ft_strlen(commands[0])) && 
		!is_inside_quotes(commands[0], ft_strnstr(commands[0], 
				"<<", ft_strlen(commands[0]))))
	{
		set_heredoc_alone(commands[0], shell);
		return ;
	}
	handle_single_command(commands[0], shell);
	return ;
}

int	is_heredoc(const char *cmd)
{
	return (ft_strnstr(cmd, "<<", ft_strlen(cmd)) && 
		!is_inside_quotes(cmd, ft_strnstr(cmd, "<<", ft_strlen(cmd))));
}

void	process_command(char **commands, int *i, int *prev_fd, t_shell *shell)
{
	int				pipe_fd[2];
	pid_t			pid;
	t_process_info	info;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (is_heredoc(commands[*i]))
	{
		*prev_fd = set_heredoc(commands[*i], shell);
		(*i)++;
		return ;
	}
	pid = setup_pipe(commands, *i, pipe_fd, shell);
	if (pid == -1)
		return ;
	info.command = commands[*i];
	info.prev_fd = *prev_fd;
	info.pipe_fd[0] = pipe_fd[0];
	info.pipe_fd[1] = pipe_fd[1];
	info.shell = shell;
	if (pid == 0)
		child_process(&info);
	else
		parent_process(commands, *i, prev_fd, pipe_fd);
	(*i)++;
}

// void	execute_pipeline(char **commands, t_shell *shell)
// {
// 	int	prev_fd;
// 	int	i;

// 	prev_fd = -1;
// 	i = 0;
// 	if (shell->pipe_count == 0)
// 		return (handle_no_pipe(commands, shell));
// 	while (commands[i])
// 	{
// 		process_command(commands, &i, &prev_fd, shell);
// 		if (prev_fd < 0)
// 			return ;
// 	}
// 	wait_for_children(shell);
// }

// void	count_pipes(char **before_pipe, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (before_pipe[i + 1] != NULL)
// 		i++;
// 	shell->pipe_count = i;
// }

// int	check_redirection_syntax(char *str, int *j)
// {
// 	if (str[*j + 1] == '<' || str[*j + 1] == '>')
// 		(*j)++;
// 	(*j)++;
// 	while (str[*j] == ' ' || str[*j] == '\t')
// 		(*j)++;
// 	if (str[*j] == '\0')
// 		return (1);
// 	return (0);
// }

// int	check_syntax_errors(char **before_pipe, t_shell *shell)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (before_pipe[i] != NULL)
// 	{
// 		j = 0;
// 		while (before_pipe[i][j] != '\0')
// 		{
// 			if (before_pipe[i][j] == '<' || before_pipe[i][j] == '>')
// 			{
// 				if (check_redirection_syntax(before_pipe[i], &j) != 0)
// 				{
// 					printf("minishell: syntax error \n");
// 					shell->last_status = 2;
// 					return (1);
// 				}
// 			}
// 			else
// 				j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// void	free_string_array(char **arr)
// {
// 	int	j;

// 	j = 0;
// 	while (arr[j] != NULL)
// 	{
// 		free(arr[j]);
// 		j++;
// 	}
// 	free(arr);
// }

// int	cleanup_and_return(char **before_pipe, t_shell *shell)
// {
// 	if (before_pipe)
// 		free_string_array(before_pipe);
// 	if (shell->delimiters)
// 		free_delimiters(shell);
// 	return (shell->last_status);
// }

// int	handle_empty_input(char **before_pipe, t_shell *shell)
// {
// 	if (before_pipe)
// 		free_string_array(before_pipe);
// 	if (shell->delimiters)
// 		free_delimiters(shell);
// 	return (shell->last_status);
// }

// int	handle_input(char *input, t_shell *shell)
// {
// 	char	**before_pipe;

// 	shell->full_input = input;
// 	shell->pipe_count = 0;
// 	before_pipe = ft_split(input, '|');
// 	if (input == NULL || *input == '\0')
// 		return (handle_empty_input(before_pipe, shell));
// 	if (check_syntax_errors(before_pipe, shell) != 0)
// 		return (cleanup_and_return(before_pipe, shell));
// 	count_pipes(before_pipe, shell);
// 	if (before_pipe[0])
// 		execute_pipeline(before_pipe, shell);
// 	return (cleanup_and_return(before_pipe, shell));
// }

// int	handle_input(char *input, t_shell *shell)
// {
// 	char	**before_pipe;
// 	int		j;
// 	int		i;

// 	shell->full_input = input;
// 	shell->pipe_count = 0;
// 	i = 0;
// 	j = 0;
// 	before_pipe = ft_split(input, '|');
// 	while (before_pipe[i] != NULL)
// 	{
// 		j = 0;
// 		while (before_pipe[i][j] != '\0')
// 		{
// 			if ((before_pipe[i][j] == '<' || before_pipe[i][j] == '>'))
// 			{
// 				if (before_pipe[i][j + 1] == '<' || 
// 					before_pipe[i][j + 1] == '>')
// 					j++;
// 				j++;
// 				while (before_pipe[i][j] == ' ' || before_pipe[i][j] == '\t')
// 					j++;
// 				if (before_pipe[i][j] == '\0')
// 				{
// 					printf("minishell: syntax error \n");
// 					shell->last_status = 2;
// 					free(before_pipe[i]);
// 					free(before_pipe);
// 					return (shell->last_status);
// 				}
// 			}
// 			else
// 				j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	j = 0;
// 	if (input == NULL || *input == '\0')
// 	{
// 		if (before_pipe)
// 		{
// 			j = 0;
// 			while (before_pipe[j] != NULL)
// 			{
// 				free(before_pipe[j]);
// 				j++;
// 			}
// 			free(before_pipe);
// 		}
// 		if (shell->delimiters)
// 			free_delimiters(shell);
// 		return (shell->last_status);
// 	}
// 	while (before_pipe[shell->pipe_count + 1] != NULL)
// 		shell->pipe_count++;
// 	if (before_pipe[i])
// 		execute_pipeline(before_pipe, shell);
// 	if (before_pipe)
// 	{
// 		j = 0;
// 		while (before_pipe[j] != NULL)
// 		{
// 			free(before_pipe[j]);
// 			j++;
// 		}
// 		free(before_pipe);
// 	}
// 	if (shell->delimiters)
// 		free_delimiters(shell);
// 	return (shell->last_status);
// }
