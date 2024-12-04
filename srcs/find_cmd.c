/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:49:02 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/08 15:43:10 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

char	*get_env_value(const char *name, char **env)
{
	int			i;
	size_t		len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*find_next_path(char **path_ptr)
{
	char	*start;
	char	*end;
	char	*result;

	if (!*path_ptr || **path_ptr == '\0')
		return (NULL);
	start = *path_ptr;
	end = ft_strchr(start, ':');
	if (end)
	{
		result = ft_substr(start, 0, end - start);
		*path_ptr = end + 1;
	}
	else
	{
		result = safe_strdup(start);
		*path_ptr = NULL;
	}
	return (result);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = safe_malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	ft_memcpy(result + len1 + len2, s3, len3);
	result[len1 + len2 + len3] = '\0';
	return (result);
}

char	*get_command(char *dir_start, char *cmd)
{
	char	*full_path;
	char	*dir_end;

	while (dir_start && *dir_start)
	{
		dir_end = ft_strchr(dir_start, ':');
		if (dir_end)
			*dir_end = '\0';
		full_path = ft_strjoin3(dir_start, "/", cmd);
		if (full_path)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			safe_free(full_path);
		}
		if (!dir_end)
			break ;
		*dir_end = ':';
		dir_start = dir_end + 1;
	}
	return (NULL);
}

char	*find_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	*dir_start;

	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		return (cmd->args[0]);
	path = get_env_value("PATH", shell->env);
	if (!path)
	{
		ft_putendl_fd("PATH not found in environment", STDERR_FILENO);
		shell->path = 1;
		return (NULL);
	}
	dir_start = path;
	return (get_command (dir_start, cmd->args[0]));
}
