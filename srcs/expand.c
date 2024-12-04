/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:00:59 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/12/03 16:58:48 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

char	*let_expand(t_quote_context *ctx, t_shell *shell, char *new_cmd)
{
	char	*temp;
	char	*var_value;

	temp = NULL;
	var_value = NULL;
	if (ctx->len > 0)
	{
		temp = ft_substr(ctx->command, ctx->i, ctx->len);
		var_value = get_env_value(temp, shell->env);
		free(temp);
		if (var_value)
			new_cmd = ft_strjoin(new_cmd, var_value);
	}
	return (new_cmd);
}

char	*handle_dollar_expansion(t_quote_context *ctx, t_shell *shell, 
		char *new_cmd)
{
	char	*temp;
	char	*last;

	temp = ft_substr(ctx->command, ctx->len, ctx->i - ctx->len);
	new_cmd = ft_strjoin(new_cmd, temp);
	free(temp);
	ctx->i++;
	ctx->len = 0;
	while (ft_isalnum(ctx->command[ctx->i + ctx->len]) || 
		ctx->command[ctx->i + ctx->len] == '_')
		ctx->len++;
	if (ctx->command[ctx->i] == '?')
	{
		last = ft_itoa(shell->last_status);
		new_cmd = ft_strjoin(new_cmd, last);
		free(last);
		ctx->len = 1;
	}
	else
		new_cmd = let_expand(ctx, shell, new_cmd);
	ctx->i += ctx->len;
	ctx->len = ctx->i;
	return (new_cmd);
}

char	*append_command_segment(char *command, t_quote_context *ctx, 
		char *new_cmd)
{
	char	*temp;

	temp = NULL;
	if (ctx->i > ctx->len)
	{
		temp = ft_substr(command, ctx->len, ctx->i - ctx->len);
		new_cmd = ft_strjoin(new_cmd, temp);
		free(temp);
	}
	ctx->len = ctx->i;
	return (new_cmd);
}

char	*check_dollar(char *command, t_shell *shell)
{
	char			*new_cmd;
	t_quote_context	ctx;

	new_cmd = ft_strdup("");
	ctx = init_quote_context(command);
	if (!new_cmd)
		return (NULL);
	while (ctx.i < (int)ft_strlen(command))
	{
		if (shell->num_delimiters == 0)
			quotes_management(&ctx, shell);
		if (!ctx.in_single_quotes && command[ctx.i] == '$' && 
			command[ctx.i + 1] != '\0')
			new_cmd = handle_dollar_expansion(&ctx, shell, new_cmd);
		else
			ctx.i++;
	}
	new_cmd = append_command_segment(command, &ctx, new_cmd);
	if (ctx.in_single_quotes || ctx.in_double_quotes)
		return (print_unclosed_quotes(new_cmd, shell), NULL);
	return (new_cmd);
}

t_quote_context	init_quote_context(char *command)
{
	t_quote_context	ctx;

	ctx.command = command;
	ctx.i = 0;
	ctx.len = 0;
	ctx.in_single_quotes = 0;
	ctx.in_double_quotes = 0;
	return (ctx);
}
