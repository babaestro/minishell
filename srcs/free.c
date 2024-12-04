/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:49:35 by anschmit          #+#    #+#             */
/*   Updated: 2024/11/27 14:58:50 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "memory.h"

t_MemoryNode	*g_memory_list = NULL;

void	track_allocation(void *ptr)
{
	t_MemoryNode	*node;

	node = malloc(sizeof(t_MemoryNode));
	if (node == NULL)
		return ;
	node->ptr = ptr;
	node->next = g_memory_list;
	g_memory_list = node;
}

void	free_all_memory(void)
{
	t_MemoryNode	*current;
	t_MemoryNode	*next;

	current = g_memory_list;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		safe_free(current->ptr);
		current = next;
	}
	g_memory_list = NULL;
}

void	safe_free(void *ptr)
{
	t_MemoryNode	*current;
	t_MemoryNode	*prev;

	current = g_memory_list;
	prev = NULL;
	if (!ptr)
		return ;
	while (current != NULL)
	{
		if (current->ptr == ptr)
		{
			if (prev == NULL)
				g_memory_list = current->next;
			else
				prev->next = current->next;
			free(current);
			free(ptr);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*safe_strdup(const char *s)
{
	size_t	len;
	char	*duplicate;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	duplicate = safe_malloc(len + 1);
	if (!duplicate)
		return (NULL);
	ft_memcpy(duplicate, s, len);
	duplicate[len] = '\0';
	return (duplicate);
}

void	free_delimiters(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->delimiters)
	{
		while (i < shell->num_delimiters)
		{
			if (shell->delimiters[i])
				free(shell->delimiters[i]);
			i++;
		}
		free(shell->delimiters);
		shell->delimiters = NULL;
	}
	shell->num_delimiters = 0;
}
