/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:45:23 by rmohamma          #+#    #+#             */
/*   Updated: 2022/12/22 16:45:25 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	newline_char(t_list *head)
{
	int		i;
	t_list	*node;

	if (head == NULL)
		return (0);
	node = get_last_node(head);
	i = 0;
	while (node->data[i])
	{
		if (node->data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last_node(t_list *head)
{
	t_list	*node;

	node = head;
	while (node && node->link)
		node = node->link;
	return (node);
}

void	allocate_line(char **line, t_list *head)
{
	int	i;
	int	len;

	len = 0;
	while (head)
	{
		i = 0;
		while (head->data[i])
		{
			if (head->data[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		head = head->link;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_list(t_list *head)
{
	t_list	*temp;
	t_list	*next;

	temp = head;
	while (temp)
	{
		free(temp->data);
		next = temp->link;
		free(temp);
		temp = next;
	}
	head = NULL;
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
