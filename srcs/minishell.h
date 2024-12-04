/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:00:12 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/03 17:08:36 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h> 
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define GREEN "\033[1;32m"
# define RESET "\033[0m"

# define MAX_ARGS 128

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HERE_DOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_output;
	int					old_out;
	int					new_out;
	int					old_in;
	int					new_in;
	int					arg_count;
	char				*cmd_path;
	t_redirection		*redirections;
	int					flag;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char		**env;
	char		*full_input;
	t_command	*commands;
	int			cmd_count;
	int			last_status;
	int			path;
	int			pipe_count;
	char		**delimiters;
	int			num_delimiters;
}	t_shell;

typedef struct s_part
{
	char			*str;
	struct s_part	*next;
}	t_part;

typedef struct s_process_info
{
	char	*command;
	int		prev_fd;
	int		pipe_fd[2];
	t_shell	*shell;
}	t_process_info;

typedef struct s_quote_context 
{
	char	*command;
	int		i;
	int		len;
	int		in_single_quotes;
	int		in_double_quotes;
}	t_quote_context;

typedef struct s_heredoc_context
{
	int		fd;
	char	*line;
	char	*line_parsed;
	int		i;
	char	*input;
	t_shell	*shell;
}	t_heredoc_context;

char				*read_input(void);
t_token				*tokenize(char *input);
void				add_token_to_list(t_token **tokens, \
					t_token	**current_token, t_token *new_token);
void				handle_cases(char **current, t_token *new_token);
void				handle_quotations(char **current, t_token *new_token);
void				handle_operators(char **current, t_token *new_token);
void				check_operators(t_token *new_token);
void				handle_words(char **current, t_token *new_token);
char				*ft_strndup(const char *s, size_t n);
t_token				*allocate_token(void);
void				free_tokens(t_token *tokens);
int					handle_input(char *input, t_shell *shell);
int					process_tokens(t_token *tokens, t_shell *shell);
void				initialize_signals(void);
void				handle_signals(int signum);
void				handle_sig_c(int sig);
void				signals_command(void);
void				sigint_handler(int sig);
char				*find_command(t_command *cmd, t_shell*shell);
t_command			*create_commands(t_token *tokens, t_shell *shell);
int					exec_builtin(t_command *command, t_shell *shell, \
					t_token *token);
void				execute_command(t_command *cmd, t_shell *shell, \
					t_token *token);
char				*get_env_value(const char *name, char **env);
t_shell				*initialize_shell(char **envp);
int					count_env_vars(char **envp);
char				**copy_env(char **envp);
void				free_env(char **env);
void				pwd_builtin(t_shell *shell);
int					cd_builtin(int nr_args, t_command *command, t_shell *shell);
void				env_builtin(int nr_args, t_shell *shell, \
					t_command *command);
int					unset_env_var(t_shell *shell, char *var_name);
char				*copy_until_char(char *s1, char c);
int					unset_builtin(t_shell *shell, char **args);
int					is_valid_identifier(const char *str);
int					validate_input(t_shell *shell, char *new_var);
int					modify_existing_env(t_shell *shell, char *new_var, \
					size_t name_len);
char				**allocate_new_environ(t_shell *shell, size_t env_size);
int					cp_env(char **new_environ, char **old_env, size_t env_size);
int					export_builtin(char **args, t_shell *shell);
void				echo_builtin(char **arg, t_token *token, t_shell *shell);
void				exit_builtin(int nr_args, t_command	*command, \
					t_shell *shell);
int					ft_isnumber(char *str);
void				exec_external(t_command *cmd, t_shell *shell);
void				free_shell(t_shell *shell);
void				free_env(char **env);
int					redirect_operators(t_token *token, t_command *cmd, \
					t_shell *shell);
int					redirect_output(t_command *cmd, char *filename);
int					redirect_append(t_command *cmd, char *filename);
int					redirect_input(t_command *cmd, char *filename, \
					t_shell *shell);
char				*find_filename(t_command *cmd);
void				ft_correctargs(t_command *cmd);
void				ft_correctargsin(t_command *cmd);
void				safe_free(void *ptr);
char				*ft_look_for_variable(t_shell *shell, char *arg, int k);
char				*check_dollar(char *command, t_shell *shell);
int					set_heredoc(char *input, t_shell *shell);
void				get_delimiter(char *input, t_shell *shell);
void				free_delimiters(t_shell *shell);
void				handle_single_command(char *command, t_shell *shell);
int					set_heredoc_alone(char *input, t_shell *shell);
char				*find_last_filename(t_command *cmd, const char *operator);
int					apply_redirections(t_command *cmd, t_shell *shell);
void				cleanup_redirections(t_redirection *redirections);
int					is_inside_quotes(const char *str, const char *substr);
int					parse_redirections(t_token *token, t_command *cmd);
int					apply_multiple_redirections(t_command *cmd, t_shell *shell);
int					apply_other_redirections(t_command *cmd, t_shell *shell);
int					has_multiple_redirections(t_command *cmd);
int					multiple_in(t_redirection *current, int fd_in, \
					t_shell *shell);
int					multiple_out(t_redirection *current, int fd_out, \
					t_shell *shell);
int					multiple_append(t_redirection *current, int fd_out, \
					t_shell *shell);
void				close_multiple(t_command *cmd, int fd_in, int fd_out);
int					check_syntax_errors(char **before_pipe, t_shell *shell);
void				free_string_array(char **arr);
int					cleanup_and_return(char **before_pipe, t_shell *shell);
int					handle_empty_input(char **before_pipe, t_shell *shell);
int					handle_input(char *input, t_shell *shell);
void				wait_for_children(t_shell *shell);
void				wait_status(int status, t_shell *shell);
void				close_stdout(int pipe_fd_1, int pipe_fd_0);
void				close_stdin(int prev_fd);
int					is_inside_quotes(const char *str, const char *substr);
void				child_process(t_process_info *info);
int					parent_process(char **commands, int i, int *prev_fd, \
					int pipe_fd[2]);
int					setup_pipe(char **commands, int i, int pipe_fd[2], \
					t_shell *shell);
void				execute_pipeline(char **commands, t_shell *shell);
void				count_pipes(char **before_pipe, t_shell *shell);
int					check_redirection_syntax(char *str, int *j);
void				handle_no_pipe(char **commands, t_shell *shell);
int					is_heredoc(const char *cmd);
void				process_command(char **commands, int *i, \
					int *prev_fd, t_shell *shell);
char				*join(char *l_limit, char *str, char *buff);
char				*ft_strjoin2(char *l_limit, char *buff);
char				*process_quote(char **current, char quote);
void				child_heredoc(char *input, t_shell *shell);
void				parent_heredoc(pid_t pid, t_shell *shell);
int					setup_heredoc(t_shell *shell);
int					process_heredoc_content(int fd, const char *del, \
					t_shell *shell);
int					write_to_file(int fd, const char *content);
char				*read_line_and_check_delimiter(const char *delimiter);
int					open_temp_file(const char *filename, int flags, \
					mode_t mode);
int					ft_isnumber(char *str);
char				*ft_strndup(const char *s, size_t n);
char				*copy_until_char(char *s1, char c);
t_quote_context		init_quote_context(char *command);
void				quotes_management(t_quote_context *ctx, t_shell *shell);
void				print_unclosed_quotes(char *new_cmd, t_shell *shell);
char				*append_command_segment(char *command, \
					t_quote_context *ctx, char *new_cmd);
char				*handle_dollar_expansion(t_quote_context *ctx, \
					t_shell *shell, char *new_cmd);
char				*let_expand(t_quote_context *ctx, t_shell *shell, \
					char *new_cmd);
t_heredoc_context	init_heredoc_context(char *input, t_shell *shell);
void				cleanup_heredoc_context(t_heredoc_context *ctx);
int					handle_line(t_heredoc_context *hd);
int					process_single_delimiter(t_heredoc_context *hd);
int					process_heredoc_input(t_heredoc_context *hd);
void				handle_heredoc_child_process(int heredoc_fd, \
					char *input, t_shell *shell);
void				handle_heredoc_parent_process(int heredoc_fd, pid_t pid, \
					t_shell *shell);

#endif