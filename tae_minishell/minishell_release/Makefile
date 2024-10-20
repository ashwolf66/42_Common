CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
NAME := minishell
MS_DIR := ./lib/libms/
INCLUDES_DIR := ./includes/
SRCS_DIR := ./srcs/

SRCS := $(SRCS_DIR)/minishell.c \
	$(SRCS_DIR)/ms_check_pipe_pair_recur.c \
	$(SRCS_DIR)/ms_check_quote_recur.c \
	$(SRCS_DIR)/ms_detect_parse_err.c \
	$(SRCS_DIR)/ms_front_end.c \
	$(SRCS_DIR)/ms_get_chunk.c \
	$(SRCS_DIR)/ms_make_dic.c \
	$(SRCS_DIR)/ms_make_job.c \
	$(SRCS_DIR)/ms_pipeline_detect_err.c \
	$(SRCS_DIR)/ms_pipeline_parse.c \
	$(SRCS_DIR)/ms_pipeline_tokenize.c \
	$(SRCS_DIR)/ms_post_process.c \
	$(SRCS_DIR)/ms_post_process_utils.c \
	$(SRCS_DIR)/ms_readline.c \
	$(SRCS_DIR)/ms_remove_quote.c \
	$(SRCS_DIR)/ms_sh_param_expan.c \
	$(SRCS_DIR)/ms_split_cmd.c \
	$(SRCS_DIR)/ms_system.c \
	$(SRCS_DIR)/ms_tokenizer.c \
	$(SRCS_DIR)/ms_tokenizer_utils.c \
	$(SRCS_DIR)/ms_utils0.c \
	$(SRCS_DIR)/ms_utils1.c \
	$(SRCS_DIR)/ms_vector.c \
	$(SRCS_DIR)/_sh_param_expan.c

TEMP := ./minishell.o \
	./ms_check_pipe_pair_recur.o \
	./ms_check_quote_recur.o \
	./ms_detect_parse_err.o \
	./ms_front_end.o \
	./ms_get_chunk.o \
	./ms_make_dic.o \
	./ms_make_job.o \
	./ms_pipeline_detect_err.o \
	./ms_pipeline_parse.o \
	./ms_pipeline_tokenize.o \
	./ms_post_process.o \
	./ms_post_process_utils.o \
	./ms_readline.o \
	./ms_remove_quote.o \
	./ms_sh_param_expan.o \
	./ms_split_cmd.o \
	./ms_system.o \
	./ms_tokenizer.o \
	./ms_tokenizer_utils.o \
	./ms_utils0.o \
	./ms_utils1.o \
	./ms_vector.o \
	./_sh_param_expan.o

OBJS := $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	make -C $(MS_DIR)
	$(CC) -I/usr/include -g -I $(INCLUDES_DIR) -c $(SRCS)
	mv $(TEMP) ./srcs/
	$(CC) -o $(NAME) $(OBJS) -L$(MS_DIR) -lms -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $?

all : $(NAME)

clean :
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	
fclean :
	make clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re :
	make fclean
	make all
.PHONY : all clean fclean re
