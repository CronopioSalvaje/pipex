CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS = Srcs/pipex.c

OBJS = Srcs/pipex.o

INC = Includes/

NAME = pipex

all : $(NAME)

lib : $(LIBFT)

$(LIBFT) :
	make -C Includes/libft	
	cp Includes/libft/libft.a Includes/


$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -c 
	cp *.o Srcs/
	rm *.o

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -fPIE -lreadline -lcurses -L $(INC) -lft -o $(NAME) -g 

env :
	$(CC) $(CFLAGS) Srcs/env.c -lreadline -L $(INC) -lft -o env

dir :
	$(CC) $(CFLAGS) tests/dir.c -lreadline -L $(INC) -lft -o dir

tputs :
	$(CC) $(CFLAGS) tests/tputs.c -lreadline -lcurses -L $(INC) -lft -o tputs

clean :
	rm -f Srcs/*.o
	make clean -C Includes/libft	

fclean : clean
	rm -f $(NAME)

re : fclean all


