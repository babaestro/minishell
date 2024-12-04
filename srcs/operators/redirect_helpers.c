/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:52:30 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/02 17:29:55 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

char	*find_filename(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (ft_strncmp((const char *)cmd->args[i], (const char *)">>", 
				ft_strlen(cmd->args[i])) == 0 && cmd->args[i + 1])
			return (cmd->args[i + 1]);
		else if (ft_strncmp((const char *)cmd->args[i], 
				(const char *)">", 
				ft_strlen(cmd->args[i])) == 0 && cmd->args[i + 1])
			return (cmd->args[i + 1]);
		else if (ft_strncmp((const char *)cmd->args[i], 
				(const char *)"<", 
				ft_strlen(cmd->args[i])) == 0 && cmd->args[i + 1])
			return (cmd->args[i + 1]);
		i++;
	}
	return (NULL);
}

char	*find_last_filename(t_command *cmd, const char *operator)
{
	char	*last_filename;
	int		i;

	last_filename = NULL;
	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (ft_strncmp(cmd->args[i], operator, ft_strlen(cmd->args[i])) == 0 && 
			cmd->args[i + 1] != NULL)
			last_filename = cmd->args[i + 1];
		i++;
	}
	return (last_filename);
}

void	ft_correctargs(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->args[i] != NULL)
	{
		if (ft_strncmp(cmd->args[i], ">>", 
				ft_strlen(cmd->args[i])) == 0 || ft_strncmp(cmd->args[i], ">", 
				ft_strlen(cmd->args[i])) == 0 || ft_strncmp(cmd->args[i], "<", 
				ft_strlen(cmd->args[i])) == 0)
		{
			i += 2;
			if (cmd->args[i] == NULL)
				break ;
		}
		else
		{
			cmd->args[j] = cmd->args[i];
			i++;
			j++;
		}
	}
	cmd->args[j] = NULL;
}

int	check_redirection_syntax(char *str, int *j)
{
	if (str[*j + 1] == '<' || str[*j + 1] == '>')
		(*j)++;
	(*j)++;
	while (str[*j] == ' ' || str[*j] == '\t')
		(*j)++;
	if (str[*j] == '\0')
		return (1);
	return (0);
}
