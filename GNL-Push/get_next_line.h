/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:05:39 by rmohamma          #+#    #+#             */
/*   Updated: 2022/12/15 14:06:01 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*data;
	struct s_list	*link;
}t_list;

char	*get_next_line(int fd);
int		newline_char(t_list *head);
t_list	*get_last_node(t_list *head);
void	read_after_list(int fd, t_list **head);
void	create_list(t_list **head, char *buffer, int bytes);
void	create_line(t_list *head, char **line);
void	allocate_line(char **line, t_list *head);
void	refreshed_list(t_list **head);
int		ft_strlen(const char *str);
void	free_list(t_list *head);
#endif
