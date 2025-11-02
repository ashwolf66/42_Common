SRC_MAN = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_striteri.c  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c 
SRC_BON = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
ifdef BONUS
	SRCS = ${SRC_MAN} ${SRC_BON}	
else
	SRCS = ${SRC_MAN}
endif
OBJS = ${SRCS:.c=.o}
OBJS_MAN = ${SRC_MAN:.c=.o}
OBJS_BON = ${SRC_BON:.c=.o}
OBJ = ${OBJS_MAN} ${OBJS_BON}
TARGET = libft.a
INCLUDE = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc

.PHONY: all re clean fclean bonus

all : ${TARGET}

${TARGET} : ${OBJS}
	${AR} ${TARGET} ${OBJS}
%.o : %.c
	${CC} ${CFLAGS} -I . -c $^ -o $@

clean :
	rm -f ${OBJS} ${OBJS_BON}

fclean :
	make clean
	rm -f ${TARGET}

re : 
	make fclean
	make all

bonus :
	make BONUS=1 all
