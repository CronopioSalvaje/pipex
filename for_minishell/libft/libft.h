/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:47:16 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/08 15:36:37 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "get_next_line.h"
# include "stdio.h"
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum BOOL
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_offsets
{
	int				b_space;
	int				a_space;
	int				precision;
	int				length;
	int				s_length;
	int				blank;
	int				nbr;
	long long		llnbr;
	char			c;
}					t_offsets;

t_offsets			extract_params(char *params);

int					handle_char(va_list args, char *params);
int					handle_string(va_list args, char *params);
int					handle_int(va_list args, char *params);
int					handle_pointer(va_list args, char *params);
int					handle_unsigned(va_list args, char *params);
int					handle_hexlower(va_list args, char *params);
int					handle_hexupper(va_list args, char *params);
int					handle_percent(va_list args, char *params);
int					ft_printf(const char *str, ...);
void				ft_putchar(char c);
void				ft_putnbr(int nb);
int					count_digits_from_nb(long long int nb, t_bool count_sign);
int					ft_printhex(long long int lnbr, int start, char *base);
int					print_char(int nb, char c);
int					extract_number(char *params);
int					count_digits(char *params);
int					is_in_array(char c, char *params);
int					check_zero_rule_i(t_offsets off, int reads, int nbr,
						char *params);
int					find_index(char c, char *params);
int					count_digits_from_hex(long long int lnbr, int start);
int					write_number(long nb, t_bool print_sign);
int					write_char(char c);
int					write_str(char *str);
int					sharp_rule(t_offsets off, int reads, char *params);
int					check_space_rule_i(t_offsets off, int reads, int nbr,
						char *params);
int					check_plus_rule_i(int nbr, char *params);
int					check_minus_rule_hex(t_offsets off, int reads, char *params,
						char *base);
int					check_zero_rule_hex(t_offsets off, int reads, char *params);
int					check_dot_rule_hex(t_offsets off, int reads, char *params);
int					write_nstr(char *str, int len);
int					get_argslength(const char *str, char tests[9]);
int					handle_params_int(char *params, int i, int reads,
						t_offsets off);
int					handle_params_uint(char *params, unsigned int i, int reads,
						t_offsets off);
int					count_digits_from_uint(unsigned int nb);
int					check_zero_rule_u(t_offsets off, int reads, int nbr,
						char *params);
int					check_space_rule_u(t_offsets off, int reads, int nbr,
						char *params);
int					check_zero_rule_str(t_offsets off, int reads, char *params);
int					check_minus_rule_str(t_offsets off, int reads,
						char *params);
int					check_space_rule_str(t_offsets off, int reads,
						char *params);
int					check_dot_rule_str(t_offsets off, int reads, char *str,
						char *params);

/* Fonctions de la libc*/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(char c);
size_t				count_word(char const *s, char c);
size_t				ft_strlen(const char *s);
void				ft_putstr(char *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_ftoa(float n, int precision);
char				*ft_to_lower_case(char *str);
char				*ft_to_upper_case(char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
/* Fonctions supplementaires*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*check_base(char *base, char *check);
int					check_error(char *base);
int					in_base(char *base, char c, int *getindex);
long				get_number(char *str, char *base);
long				ft_atoi_base(char *str, char *base);
char				**ft_split_key_val(char const *s, char c);
char				*ft_strcpy(char *dest, char *src);
/* Fonctions bonus*/
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
