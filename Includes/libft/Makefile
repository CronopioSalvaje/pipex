# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 19:03:33 by calbor-p          #+#    #+#              #
#    Updated: 2024/02/08 08:16:05 by calbor-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_putchar.c ft_putnbr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_convert_base.c ft_convert_base2.c\
ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putstr.c ft_putendl_fd.c ft_putnbr_fd.c \
arrays.c ft_printf.c handler_hex.c handler_numb.c handler_params.c handler_txt.c handler_write.c \
params.c rules_hex.c rules_int.c rules_str.c rules_u.c utils.c get_next_line.c get_next_line_utils.c 

OBJECTS = ft_putchar.o ft_putnbr.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o \
ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_convert_base.o ft_convert_base2.o\
ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o \
ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o \
ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putstr.o ft_putendl_fd.o ft_putnbr_fd.o \
arrays.o ft_printf.o handler_hex.o handler_numb.o handler_params.o handler_txt.o handler_write.o \
params.o rules_hex.o rules_int.o rules_str.o rules_u.o utils.o get_next_line.o get_next_line_utils.o 

BONUSSRC = ft_lstadd_front_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUSOBJ =  ft_lstadd_front_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o \
ft_lstadd_back_bonus.o ft_lstdelone_bonus.o ft_lstclear_bonus.o ft_lstiter_bonus.o ft_lstmap_bonus.o

CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

$(OBJECTS) : $(SOURCES) 
	$(CC) $(CFLAGS) -c $(SOURCES)

bonus : $(BONUSSRC) $(NAME)
	$(CC) $(CFLAGS) -c $(BONUSSRC)
	ar -rs $(NAME) $(BONUSOBJ)

.PHONY : clean fclean re bonus

clean : 
	rm -rf $(OBJECTS) $(BONUSOBJ)

fclean : clean
	rm -rf $(NAME)

re :  fclean all
