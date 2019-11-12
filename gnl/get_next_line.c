/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:38:44 by lcassaun          #+#    #+#             */
/*   Updated: 2019/11/12 18:40:52 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			gnl_fill(t_cont *t, char **tmp, long int buff)
{
	t->len += t->tmp;
	t->tmp = 0;
	*tmp = t->str;
	t->str = ft_chmalloc_zend(buff);
	t->rm = t->str;
	return (0);
}

int			gfree(t_cont *t, char **tmp, long int i)
{
	if (*tmp)
	{
		t->str = ft_strjoin(*tmp, t->str - i);
		free(*tmp);
		free(t->rm);
	}
	else
		t->str = t->str - i;
	return (1);
}

long int	gnl_n(t_cont *t, long int buff, char *tmp)
{
	long int		i[3];

	while ((i[0] = gnl_fill(t, &tmp, buff)) == 0)
	{
		i[2] = buff;
		while (i[2] != 0)
		{
			if ((i[1] = read(t->fd, t->str, BUFF_SIZE)) == 0)
			{
				if (i[2] == buff && (t->str = ft_strdup(tmp)))
					return (-2);
				return (-1 * gfree(t, &tmp, i[0]));
			}
			t->tmp += i[1];
			t->str[i[1]] = '\0';
			while (*t->str != '\0')
				if (++i[0] && (*(t->str)++ == '\n') && (gfree(t, &tmp, i[0])))
					return (t->len + i[0] - 1);
			i[2] -= i[1];
		}
		buff *= 2 * gfree(t, &tmp, i[0]);
	}
	return (0);
}

char		*gnl_str(t_cont *t, char *tmp, long int i)
{
	if (t->str && (i = ft_findchr(t->str, '\n')) >= 0)
	{
		t->join = ft_memstrncpy(NULL, t->str, i++);
		tmp = t->str;
		t->str = ft_strdup(t->str + i);
		free(tmp);
		t->len -= i;
		return (t->join);
	}
	if ((i = gnl_n(t, BUFF_SIZE, NULL)) == -1)
	{
		t->join = ft_strdup(t->str);
		return (t->join + ft_free_enull(&(t->str)));
	}
	if (i == -2)
	{
		if (t->len != 0 && (t->join = ft_memstrncpy(NULL, t->str, t->len)))
			return (t->join + ft_free_enull(&(t->str)));
		return (NULL);
	}
	t->join = ft_memstrncpy(NULL, t->str, i++);
	tmp = t->str;
	t->str = ft_strdup(t->str + i);
	t->len -= i;
	free(tmp);
	return (t->join);
}

int			get_next_line(const int fd, char **line)
{
	static t_node	*head;
	t_node			*curr;
	int				i;

	i = 0;
	if (read(fd, 0, 0) == -1)
		return (-1);
	if (!(curr = ft_find_node_fd(head, fd)))
	{
		curr = ft_create_node(ft_create_cont_fd(fd, NULL));
		head = ft_insert_node(head, curr, (void *)ft_cmp_fd);
		i = 1;
	}
	if (i == 0 && (((t_cont *)(curr->d))->str == NULL))
	{
		free(curr);
		return (0);
	}
	if ((*line = ft_strdup(gnl_str((t_cont *)(curr->d), NULL, 0))) != NULL)
	{
		ft_free_enull(&(((t_cont *)(curr->d))->join));
		return (1);
	}
	return (0);
}
