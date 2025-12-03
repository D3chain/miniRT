/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:24:44 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/03 11:21:44 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>

typedef unsigned char	t_byte;
typedef size_t			t_op_t;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_skipspaces(const char **nptr);

//	<stdio.h>
int		ft_printf(const char *__format, ...);

//	<ctype.h>
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_toupper_str(char *str);
char	*ft_tolower_str(char *str);

//	<string.h>
char	*ft_strcpy(char *dest, const char *src);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strrcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_nbrlen(long nbr);
size_t	ft_nbrlen_base(long nbr, int base);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

//	<bsd/string.h>
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);

//	<stdlib.h>
int		ft_atoi(const char *nptr);
int		ft_atoi_base(const char *nptr, const char *base);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void **ptr, size_t old_size, size_t new_size);

//	utilities
ssize_t	ft_putchar(char c);
ssize_t	ft_putstr(char *str);
ssize_t	ft_puterr(char *errmsg);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_split_free(char **strs);
char	*ft_itoa(int n);
void	ft_itoa_static(int n, char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putunbr(unsigned int nbr);
ssize_t	ft_putnbr(int nbr);
ssize_t	ft_putnbr_fd(int n, int fd);
ssize_t	ft_putnbr_base(int nbr, char *base_charset);
ssize_t	ft_putunbr_base(unsigned int nbr, char *base_charset);
ssize_t	ft_putaddr_hex(uintptr_t addr);

// bonuses / linked lists
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void	*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstfree(t_list *data);

// misc / maths
double	ft_toradian(double angle);

//	get_next_line
# if BUFFER_SIZE >= 4096
#  undef BUFFER_SIZE
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# define FD_MAX 1024

char	*getd_next_line(int fd);
char	*gets_next_line(int fd);

//	utils
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
