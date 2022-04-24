/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:59:10 by eozben            #+#    #+#             */
/*   Updated: 2022/01/15 22:46:57 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_line(t_line *line)
{
	line->position = 0;
	line->alloc = BUFFER_SIZE;
	line->str = malloc(sizeof(char) * line->alloc);
	if (!line->str)
		return (-1);
	return (0);
}

char	read_buf_char(t_buf *buf, int fd)
{
	char	c;

	if (buf->start >= buf->end)
	{
		buf->end = read(fd, buf->buf, BUFFER_SIZE);
		buf->start = 0;
		if (buf->end <= 0)
			return (buf->end);
	}
	c = buf->buf[buf->start];
	buf->start++;
	return (c);
}

int	append_to_line(t_line *line, char c)
{
	char	*new_str;

	if (line->position >= line->alloc)
	{
		line->alloc = line->position + line->alloc;
		new_str = malloc(sizeof(char) * line->alloc);
		if (!new_str)
			return (-1);
		ft_strcpy(new_str, line->str, line->position);
		free(line->str);
		line->str = new_str;
	}
	line->str[line->position] = c;
	line->position++;
	return (0);
}

char	*terminate_string(t_line *line)
{
	char	*str;

	if (line->position == 0)
		return (free_str(line->str));
	str = malloc(sizeof(char) * line->position + 1);
	if (!str)
		return (free_str(line->str));
	ft_strcpy(str, line->str, line->position);
	str[line->position] = '\0';
	free(line->str);
	return (str);
}

char	*get_next_line(int fd)
{
	t_line			line;
	static t_buf	buf[10240];
	char			c;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0 || init_line(&line) == -1)
		return (NULL);
	while (1)
	{
		c = read_buf_char(&buf[fd], fd);
		if (c == 0)
			break ;
		else if (c == -1)
			return (free_str(line.str));
		if (append_to_line(&line, c) == -1)
			return (free_str(line.str));
		if (c == '\n')
			break ;
	}
	return (terminate_string(&line));
}
