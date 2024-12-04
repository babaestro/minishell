/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:27:19 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/10 12:28:03 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef MAXFD
#  define MAXFD 1024
# endif

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
int		ft_atoi(const char *nptr);
char	*ft_strchr(char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *l_limit, char *buff);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_itoa(int n);
void	ft_putnbr_fd(int n, int fd);
int		ft_printf(const char *format, ...);
int		ft_printpercent(const char **format, int *count);
int		ft_printunsigned(va_list args, const char **format, int *count);
int		ft_printint(va_list args, const char **format, int *count);
int		ft_printstr(va_list args, const char **format, int *count);
int		ft_printchar(va_list args, const char **format, int *count);
int		ft_putnbr(va_list args, const char **format, int *count);
int		ft_printother(va_list args, const char **format, int *count);
int		ft_putunsigned(va_list args, const char **format, int *count);
int		ft_puthex(va_list args, const char **format, int *count);
int		ft_puthexup(va_list args, const char **format, int *count);
int		ft_printpointer(va_list args, const char **format, int *count);
char	*ft_get_current_line(char *line_limit);
char	*ft_new_line_limit(char *line_limit);
char	*get_next_line(int fd);

#endif
