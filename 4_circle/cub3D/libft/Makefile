SRCS =	ft_atodb.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa_i.c \
		ft_itoa_ui.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strdup.c \
		ft_striteri.c  \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		char_print.c \
		ft_printf.c \
		ft_putnbr_base.c \
		hex_print.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstlast.c \
		ft_lstsize.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line_utils.c \
		get_next_line.c
OBJS = ${SRCS:.c=.o}
TARGET = libft.a
INCLUDE = .
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc

.phony : all re clean fclean

all : ${TARGET}

${TARGET} : ${OBJS}
	${AR} ${TARGET} ${OBJS}
%.o : %.c
	${CC} ${CFLAGS} -I . -c $^ -o $@ -g

clean :
	rm -f ${OBJS}

fclean :
	make clean
	rm -f ${TARGET}

re : 
	make fclean
	make all
