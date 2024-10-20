CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libms.a
INC = libms.h
SRCS = ./ms_isascii.c \
       ./ms_memcpy.c \
       ./ms_putstr_fd.c \
       ./ms_strlcat.c \
       ./ms_strrchr.c \
       ./ms_atoi.c \
       ./ms_isdigit.c \
       ./ms_memmove.c \
       ./ms_split.c \
       ./ms_strlcpy.c \
       ./ms_strtrim.c \
       ./ms_bzero.c \
       ./ms_isprint.c \
       ./ms_memset.c \
       ./ms_strchr.c \
       ./ms_strlen.c \
       ./ms_substr.c \
       ./ms_calloc.c \
       ./ms_itoa.c \
       ./ms_putchar_fd.c \
       ./ms_strdup.c \
       ./ms_strmapi.c \
       ./ms_tolower.c \
       ./ms_isalnum.c \
       ./ms_memchr.c \
       ./ms_putendl_fd.c \
       ./ms_striteri.c \
       ./ms_strncmp.c \
       ./ms_toupper.c \
       ./ms_isalpha.c \
       ./ms_memcmp.c \
       ./ms_putnbr_fd.c \
       ./ms_strjoin.c \
       ./ms_strnstr.c \
       ./ms_malloc.c \
       ./ms_strndup.c \
       ./ms_strcmp.c \
       ./ms_strlen_s.c \
       ./ms_strjoin_s.c \
       ./ms_glob.c
       
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = ./ms_lstnew_bonus.c \
             ./ms_lstadd_front_bonus.c \
             ./ms_lstsize_bonus.c \
             ./ms_lstlast_bonus.c \
             ./ms_lstadd_back_bonus.c \
             ./ms_lstdelone_bonus.c \
             ./ms_lstclear_bonus.c \
             ./ms_lstiter_bonus.c \
             ./ms_lstmap_bonus.c
             
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME) bonus

$(NAME) : $(OBJS)

bonus : $(OBJS) $(BONUS_OBJS)
	ar rc $(NAME) $^	

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@
	ar rc $(NAME) $@
clean :
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all

.PHONY: clean fclean re all bonus
