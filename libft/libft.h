/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi 	    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:20:32 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/08 14:15:31 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_glist
{
	char			*str_buf;
	struct s_glist	*next;
}	t_glist;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// LIB F TI
int		ft_isalpha(int ch);
int		ft_isdigit(int ch);
int		ft_isalnum(int ch);
int		ft_isascii(int ch);
int		ft_isprint(int ch);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, int len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *arr, int c, size_t n);
int		ft_memcmp(const void *arr1, const void *arr2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

// PRINT "F"
int		ft_printf(const char *format, ...);
int		ft_processor(va_list args, const char *format);
int		ft_set_format(va_list args, const char format);
int		ft_print_negative(int d, int total);
int		ft_print_num(int d, int total);
int		ft_print_char(int c);
int		ft_print_str(char *s, int total);
int		ft_print_hex(unsigned long n, const char format, int total);
int		ft_print_uint(unsigned int n, int total);
int		ft_print_ptr(void *ptr, int total);
int		ft_preprocessor(const char *format);

// GET_NEXT_LINE

void	dealloc(t_glist **list, t_glist *clean_node, char *buf);
t_glist	*find_last_node(t_glist *list);
void	polish_text(t_glist **list);
int		len_to_newline(t_glist *list);
void	copy_str(t_glist *list, char *str);
char	*line_get(t_glist *list);
int		found_newline(t_glist *list);
void	node_add(t_glist **list, char *buf);
void	create_list(t_glist **list, int fd);
char	*get_next_line(int fd);
#endif
