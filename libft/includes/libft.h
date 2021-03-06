/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcassaun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:55:12 by lcassaun          #+#    #+#             */
/*   Updated: 2019/09/24 21:28:27 by lcassaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

enum	e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct			s_rb_node
{
	void				*data;
	enum e_rb_color		color;
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	struct s_rb_node	*parent;
}						t_rb_node;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char				*ft_strncpy(char *dst, char const *src, size_t n);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
int					ft_strcmp(char const *s1, char const *s2);
size_t				ft_strlen(char const *str);
void				ft_strclr(char *s);
char				*ft_strdup(char const *src);
char				*ft_itoa(int n);
int					ft_atoi(char const *str);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *s, int c, size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *arr, int c, size_t n);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
char				*ft_strcat(char *str1, const char *str2);
char				*ft_strncat(char *str1, const char *str2, size_t n);
size_t				ft_strlcat(char *str1, const char *str2, size_t n);
char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_isalnum(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_swap(int *a, int *v);
long int			ft_abs(long int a);
long int			ft_min(long int a, long int b);
long int			ft_max(long int a, long int b);
int					ft_isblank(int c);
void				ft_lsthead(t_list **lst, t_list *new);
void				ft_lsttale(t_list **lst, t_list *new);
void				ft_lstfree(void *content, size_t content_size);
void				ft_insert_rb(t_rb_node **root, t_rb_node *t);
void				*ft_left_rotate_rb(t_rb_node *t);
void				*ft_right_rotate_rb(t_rb_node *t);
t_rb_node			*ft_create_node_rb(void *data);

#endif
