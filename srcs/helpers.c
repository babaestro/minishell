/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:30:54 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/04 13:08:02 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

int	ft_isnumber(char *str)
{
	while (*str != '\0')
	{
		if (*str == '+' || *str == '-')
			str++;
		if (*str >= 48 && *str <= 57)
			str++;
		else
			return (0);
	}
	return (1);
}

char	*ft_strndup(const char *s, size_t n)
{
	char			*duplicate;
	unsigned int	j;

	j = 0;
	duplicate = safe_malloc(sizeof(char) * (n + 1));
	if (!duplicate)
		return (NULL);
	while (s[j] != '\0' && j < n)
	{
		duplicate[j] = s[j];
		j++;
	}
	duplicate[j] = '\0';
	return (duplicate);
}

char	*copy_until_char(char *s1, char c)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	while (s1[i] != '\0' && s1[i] != c)
		i++;
	copy = (char *)safe_malloc((i + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[i] = '\0';
	return (copy);
}

// t_quote_context	init_quote_context(char *command)
// {
// 	t_quote_context	ctx;

// 	ctx.command = command;
// 	ctx.i = 0;
// 	ctx.len = 0;
// 	ctx.in_single_quotes = 0;
// 	ctx.in_double_quotes = 0;
// 	return (ctx);
// }

// char	*let_expand(t_quote_context *ctx, t_shell *shell, char *new_cmd)
// {
// 	char	*temp;
// 	char	*var_value;

// 	temp = NULL;
// 	var_value = NULL;
// 	if (ctx->len > 0)
// 	{
// 		temp = ft_substr(ctx->command, ctx->i, ctx->len);
// 		var_value = get_env_value(temp, shell->env);
// 		free(temp);
// 		if (var_value)
// 			new_cmd = ft_strjoin(new_cmd, var_value);
// 	}
// 	return (new_cmd);
// }

// char	*handle_dollar_expansion(t_quote_context *ctx, t_shell *shell, 
// 		char *new_cmd)
// {
// 	char	*temp;
// 	char	*last;

// 	temp = ft_substr(ctx->command, ctx->len, ctx->i - ctx->len);
// 	new_cmd = ft_strjoin(new_cmd, temp);
// 	free(temp);
// 	ctx->i++;
// 	ctx->len = 0;
// 	while (ft_isalnum(ctx->command[ctx->i + ctx->len]) || 
// 		ctx->command[ctx->i + ctx->len] == '_')
// 		ctx->len++;
// 	if (ctx->command[ctx->i] == '?')
// 	{
// 		last = ft_itoa(shell->last_status);
// 		new_cmd = ft_strjoin(new_cmd, last);
// 		free(last);
// 		ctx->len = 1;
// 	}
// 	else
// 		new_cmd = let_expand(ctx, shell, new_cmd);
// 	ctx->i += ctx->len;
// 	ctx->len = ctx->i;
// 	return (new_cmd);
// }

void	quotes_management(t_quote_context *ctx, t_shell *shell)
{
	if (shell->num_delimiters == 0)
	{
		if (ctx->command[ctx->i] == '\'' && ctx->in_double_quotes == 0)
			ctx->in_single_quotes = !(ctx->in_single_quotes);
		else if (ctx->command[ctx->i] == '"' && ctx->in_single_quotes == 0)
			ctx->in_double_quotes = !(ctx->in_double_quotes);
	}
}

void	print_unclosed_quotes(char *new_cmd, t_shell *shell)
{
	ft_putendl_fd("Unclosed quotes", STDERR_FILENO);
	shell->last_status = 127;
	free(new_cmd);
}
