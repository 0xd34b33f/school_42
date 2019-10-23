#include "get_next_line.h"
#include <stdio.h>

int		ft_buff(t_cont *t, char **strbuff, size_t i1, size_t buff)
{
	size_t	i2;

		if (!(i2 = read(t->fd, *strbuff, BUFF_SIZE)))
		{
			if (i1 == buff)
			{
				free(*strbuff);
				return (-3);
			}
			t->join = *strbuff - t->i_len;
			t->end = t->i_len;
			return (-2);
		}
		t->len += i2;
		*strbuff[i2] = '\0';
		while (**strbuff != '\0')
		{
			if (**strbuff++ == '\n')
			{
				t->join = *strbuff - t->i_len - 1;
				return (-1);
			}
			t->i_len++;
		}
		return (1);
}



int		ft_buff_join(size_t buff, t_cont *t, int fd, char *join)
{
	char	*strbuff;
	size_t	i1[2];

	t->i_len = 0;
	i1[0] = buff;
	t->join = NULL;
	strbuff = ft_chmalloc_zend(buff);
	while (buff != 0)
	{
		if ((i1[1] = ft_buff(t, &strbuff, i1[0], buff)) == -2)
			return (-2);
		if (i1[1] == -3)
			return (-3);
		if (i1[1] == -1)
			return (t->i_len + 1);
		buff -= BUFF_SIZE;
	}
	t->join = strbuff - t->i_len;
	return (-1);
}

		
int		ft_join(t_cont *t, int fd, size_t buff)
{
	char		*strrm;
	long int	i[3];

	i[1] = 0;
	i[2] = t->len;
	if ((i[0] = ft_findchr(t->str, '\n')) >= 0 && (t->end = i[0]))
		return (1);
	while (strrm = t->str - t->tmp)
	{
		if ((i[0] = ft_buff_join(buff, t, fd, t->join)) == -3)
			return (-1);
		t->str = ft_strjoin(t->str, t->join);
		free(strrm);
		t->tmp = 0;
		if (i[0] == -2 && (t->len -= t->end) >= 0)
			return (-1);
		free(t->join);
		if (i[0] >= 0 && (t->end = i[2] + i[0] + i[1] - 1) >= 0)
			return (1);
		i[1] += buff;
		buff *= 2;
	}
} 

static char	*ft_str(t_cont *t, int fd, char *tmp)
{
	
	if ((t->str == NULL))
	{
		t->str = ft_chmalloc_zend(BUFF_SIZE);
		if (!(t->end = (read(fd, t->str, BUFF_SIZE))))
            return (NULL);
		(t->str)[t->len = t->end] = '\0';
	}
	if (ft_join(t, fd, BUFF_SIZE) == -1)
	{
		tmp = ft_strdup(t->str);
		free(t->str - t->tmp);
		t->tmp = 0;
		t->str = NULL;
		return (tmp);
	}
	tmp = ft_chmalloc_zend(t->end);
	ft_strncpy(tmp, t->str, t->end++);
	t->str += t->end;
	t->tmp += t->end;
	t->len -= t->end;
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static t_node	*head;
	t_node			*curr;

	if (read(fd, 0, 0) == -1)
		return (-1);
	if (!(curr = ft_find_node_fd(head, fd)))
		curr = ft_create_node(ft_create_cont_fd(fd, NULL));
	if (!head)
		head = ft_insert_node(head, curr, (void *)ft_cmp_fd);
	if ((*line = ft_str(((t_cont *)(curr->d)), fd, NULL)) != NULL)
		return (1);
	return (0);
}
