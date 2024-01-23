/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:43:45 by rmohamma          #+#    #+#             */
/*   Updated: 2022/12/22 16:43:54 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*head[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_after_list(fd, &head[fd]);
	if (!head[fd])
		return (NULL);
	create_line(head[fd], &line);
	refreshed_list(&head[fd]);
	if (head[fd]->data[0] == '\0')
	{
		free_list(head[fd]);
		head[fd] = NULL;
	}
	if (line[0] == '\0')
	{
		free_list(head[fd]);
		head[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_after_list(int fd, t_list **head)
{
	char	*buffer;
	int		bytes;

	bytes = 1;
	while (!newline_char(*head) && bytes != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		bytes = (int)read(fd, buffer, BUFFER_SIZE);
		if (!bytes || bytes == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bytes] = '\0';
		create_list(head, buffer, bytes);
		free(buffer);
	}
}

void	create_list(t_list **head, char *buffer, int bytes)
{
	int		i;
	t_list	*last_node;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->link = NULL;
	new_node->data = malloc(sizeof(char) * (bytes + 1));
	if (!new_node->data)
		return ;
	i = 0;
	while (i < bytes)
	{
		new_node->data[i] = buffer[i];
		i++;
	}
	new_node->data[i] = '\0';
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	last_node = get_last_node(*head);
	last_node->link = new_node;
}

void	create_line(t_list *head, char **line)
{
	int	i;
	int	j;

	if (!head)
		return ;
	allocate_line(line, head);
	if (*line == NULL)
		return ;
	j = 0;
	while (head)
	{
		i = 0;
		while (head->data[i])
		{
			if (head->data[i] == '\n')
			{
				(*line)[j++] = head->data[i];
				break ;
			}
			(*line)[j++] = head->data[i++];
		}
		head = head->link;
	}
	(*line)[j] = '\0';
}

void	refreshed_list(t_list **head)
{
	t_list	*last_node;
	t_list	*new_node;
	int		i;
	int		j;

	new_node = malloc(sizeof(t_list));
	if (!head || !new_node)
		return ;
	new_node->link = NULL;
	last_node = get_last_node(*head);
	i = 0;
	while (last_node->data[i] && last_node->data[i] != '\n')
		i++;
	if (last_node->data[i] && last_node->data[i] == '\n')
		i++;
	new_node->data = malloc(sizeof(char)
			* ((ft_strlen(last_node->data) - i) + 1));
	if (!new_node->data)
		return ;
	j = 0;
	while (last_node->data[i])
		new_node->data[j++] = last_node->data[i++];
	new_node->data[j] = '\0';
	free_list(*head);
	*head = new_node;
}
