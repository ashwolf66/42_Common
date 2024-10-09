/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:48:21 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 12:32:34 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMS_H
# define LIBMS_H

/* MACROS FOR CTYPE IS SERIES */

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define MS_PR 0x4000 // for ms_isprint();
# define MS_DI 0x0800 // for ms_isdigit();
# define MS_AL 0x0400 // for ms_isalpha();
# define MS_LO 0x0200 // for ms_islower();
# define MS_UP 0x0100 // for ms_isupper();
# define MS_AN 0x0008 // for ms_isalnum();
# define MS_AS 0x0001 // for ms_isascii();
# define OPEN 1
# define CLOSED 0

typedef int	t_bool;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* MANDATORY PART FUNCS */

int			ms_isalpha(int c);
int			ms_isdigit(int c);
int			ms_isalnum(int c);
int			ms_isascii(int c);
int			ms_isprint(int c);
size_t		ms_strlen(const char *s);
void		*ms_memset(void *s, int c, size_t n);
void		ms_bzero(void *s, size_t n);
void		*ms_memcpy(void *dest, const void *src, size_t n);
void		*ms_memmove(void *dest, const void *src, size_t n);
size_t		ms_strlcpy(char *dst, const char *src, size_t sz);
size_t		ms_strlcat(char *dst, const char *src, size_t sz);
int			ms_toupper(int c);
int			ms_tolower(int c);
char		*ms_strchr(const char *s, int c);
char		*ms_strrchr(const char *s, int c);
int			ms_strncmp(const char *s1, const char *s2, size_t n);
void		*ms_memchr(const void *s, int c, size_t n);
int			ms_memcmp(const void *s1, const void *s2, size_t n);
char		*ms_strnstr(const char *big, const char *little, size_t len);
int			ms_atoi(const char *nptr);
void		*ms_calloc(size_t nmemb, size_t size);
char		*ms_strdup(const char *s);
char		*ms_strndup(const char *s, size_t n);
t_list		**ms_glob(void);

/* ms ORIGINAL FUNCS */

char		*ms_substr(char const *s, unsigned int start, size_t len);
char		*ms_strjoin(char const *s1, char const *s2);
char		*ms_strtrim(char const *s1, char const *set);
char		**ms_split(char const *s, char c);
char		*ms_itoa(int n);
char		*ms_strmapi(char const *s, char (*f)(unsigned int, char));
void		ms_striteri(char *s, void (*f)(unsigned int, char*));	
void		ms_putchar_fd(char c, int fd);
void		ms_putstr_fd(char *s, int fd);
void		ms_putendl_fd(char *s, int fd);
void		ms_putnbr_fd(int n, int fd);
bool		ms_is_set(char chr, char *set);
int			ms_strcmp(const char *s1, const char *s2);
size_t		ms_strlen_s(char *str);
char		*ms_strjoin_s(char *s1, char *s2);
void		*ms_malloc(size_t sz);

/* BONUS PART FUNCS */

t_list		*ms_lstnew(void *content);
void		ms_lstadd_front(t_list **lst, t_list *new);
int			ms_lstsize(t_list *lst);
t_list		*ms_lstlast(t_list *lst);
void		ms_lstadd_back(t_list **lst, t_list *new);
void		ms_lstdelone(t_list *lst, void (*del)(void*));
void		ms_lstclear(t_list **lst, void (*del)(void*));
void		ms_lstiter(t_list *lst, void (*f)(void *));
t_list		*ms_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
