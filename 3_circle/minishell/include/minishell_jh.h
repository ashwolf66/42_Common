/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_jh.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 09:41:24 by jacha             #+#    #+#             */
/*   Updated: 2025/01/01 18:01:35 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_JH_H
# define MINISHELL_JH_H

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "minishell_hb.h"

extern int			g_status;

struct				s_pool;
struct				s_cmd;
struct				s_commend;
struct				s_sub_job;

typedef struct s_pool
{
	char			**cmd_pool;
	int				indx;
	int				r_indx;
	int				s_quote;
	int				d_quote;
	int				s_count;
	int				count_temp;
	int				count;
	size_t			row;
	size_t			col;
}					t_pool;

typedef struct s_job
{
	char			**job;
	int				num;
	int				in;
	int				out;
	int				rd;
	int				pipe;
	int				s_quote;
	int				d_quote;
	int				tem_len;
	size_t			r_indx;
	size_t			indx;
	struct s_job	*next;
}					t_job;

typedef struct s_commend
{
	char			*cmd;
	char			*temp;
	int				temp_len;
	int				indx;
	int				indx_start;
	int				s_quote;
	int				d_quote;
	int				pipe;
	int				pipe_count;
	int				count;
	int				l_direct;
	int				r_direct;
	int				l_count;
	int				r_count;
	int				di_space;
	int				len;
	size_t			size;
}					t_commend;

// main
int			ft_builtin(t_job **o_job, t_job *jobs, t_info *b_info, \
		pid_t all_pid[]);
int			check_str(char *cmd);

// cmd_pool
int			pipe_count_mal(t_commend *com, t_pool *pool);
int			add_cmd_pool(t_commend *com, t_pool *pool, t_info *b_info);
int			cmd_pipe_mal(t_commend *com, t_pool *pool, t_info *b_info);
void		ms_strlcpy(char *dest, char *src, t_commend *com, t_info *b_info);
void		cpy_env(char *dest, size_t *j, t_commend *com);
int			direct_case(t_commend *com);
int			un_direct_case(t_commend *com);
void		env_check(t_commend *com, t_info *b_info);
int			get_env_len(t_commend *com);
void		cpy_temp(t_commend *com, int i, int len);
int			ps_find_list_key(t_list *head, t_commend *cmd);
void		ms_env_check(char *src, size_t *i, t_commend *com, t_info *b_info);
int			ms_get_env_len(char *str, size_t *indx, t_commend *com);
void		ms_cpy_temp(t_commend *com, char *str, int i, int len);
int			ms_ps_find_list_key(t_info *b_info, t_commend *cmd);
void		ms_c_quote_check(char *src, int i, t_commend *com);
void		ms_strlcpy_2(char *src, char *dest, size_t *i, size_t *j);
void		ms_strlcpy_3(char *src, char *dest, size_t *i, size_t *j);

// dr_case
void		l_dr_case(int l_d, t_job *job, t_info *b_info);
void		r_dr_case(int r_d, t_job *job);
void		heredoc_case(t_job *job, t_info *b_info);
int			heredoc_start(char *name, t_info *b_info);
int			create_temp_file(char *name, t_info *b_info);
char		*find_env(char *str, t_info *b_info);
char		*env_len(char *str, int *i, t_info *b_info);
char		*hd_find_list_key(t_list *head, char *temp);
void		cpy_env_val(char *temp, char *env, int *j);
int			end_check(char *name, char *str, size_t len);

// execve_start
void		execve_start(t_job **job, t_info *b_info, int pipe);
void		start_exe(int *in, int *out);
void		end_exe(int *in, int *out);
int			builtin_check(t_job *jobs);
void		one_job(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[]);
void		not_one_job(t_job **job, t_info *b_info, pid_t pid[]);
int			execve_child(t_job **o_job, t_job *job,
				t_info *b_info, pid_t all_pid[]);
void		not_builtin_case(t_job **o_job, t_job *job,
				t_info *b_info, pid_t all_pid[]);
void		builtin_case(t_job **o_job, t_job *job,
				t_info *b_info, pid_t all_pid[]);
void		about_job(t_job *job, int fd[]);
char		*find_path(t_job **o_job, t_job *job,
				t_info *b_info, pid_t all_pid[]);
t_list		*find_exe(t_job **o_job, t_job *job,
				t_info *b_info, pid_t all_pid[]);
void		free_op(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[]);
void		not_cmd(t_job **o_job, t_job *job, t_info *b_info, pid_t all_pid[]);

// init
void		init_all(t_commend *com, t_pool *pool);
void		init_commend(t_commend *com);
void		init_pool(t_pool *pool);
void		init_pool_quote(t_pool *pool);
void		init_job(t_job *job);
void		exe_init_job(t_job *job);

// ms
void		*ms_calloc(size_t num, size_t size);
void		ms_lstadd_back(t_job **lst, t_job *new);
t_job		*ms_lstnew(char **job, int num);
void		*ms_memset(void *s, int c, size_t n);
char		**ms_split(t_pool *pool, char c);
char		**ms_strdup(char **s);

// parsing
int			parsing(t_job *jobs, t_info *b_info, char *cmd);
int			ready_struct(t_commend **com, t_pool **pool);
void		free_error_1(t_job *jobs, t_info *b_info,
				t_commend *com, t_pool *pool);
void		exit_valid_check(t_job *job);
int			ft_exit_2(t_info *b_info, t_job *jobs);
void		exit_free(t_info *b_info, t_job *jobs);
int			op_com(t_commend *com, t_pool *pool);
int			syntax_check(t_commend *com);
int			direct_count(t_commend *com);
void		syntax_error(t_commend *com, t_pool *pool);
int			remove_quote(t_job **job);
int			push_rm_quote(t_job *temp);
char		**ms_rm_strdup(t_job *job);
void		rm_dup_cpy(char *temp, t_job *s, size_t col_len);
size_t		dup_row_len(char **s);
size_t		dup_colum_len(char *s);
void		dup_cpy(char *temp, char *s);
void		pool_tokenizer(t_job **job, t_pool *pool);
void		make_job_col(t_job **job, t_pool *pool);
int			update_fd(t_job **job, t_info *b_info);
int			fd_seting(t_job *job, t_info *b_info);
char		**fd_start(char **temp, t_job *job, t_info *b_info);
int			fd_result(t_job *job, t_info *b_info);
int			fd_seting_utils(t_job *job, int *i);

// utils
int			is_whitespace(char chr);
int			is_quote(char chr);
void		c_quote_check(t_commend *com);
void		p_quote_check(t_pool *pool);
void		add_c_quote_check(t_commend *com, t_pool *pool, t_info *b_info);
void		direct_check(t_commend *com);
size_t		ms_to_strlcpy(char *dest, t_pool *s, size_t size);
size_t		ms_to_strlen(t_pool *s);
void		p_s_quote_check(t_pool *pool, size_t i);
int			j_quote_check(t_job *j);
void		syn_c_quote_check(t_commend *com);
void		direct_check_utils(t_commend *com);
int			fd_start_utils(char **temp, t_job *job, t_info *b_info, int *j);
int			ms_return_1(char *str, int i);
int			ms_return_2(char *str, int i);
int			ms_utils_1(char *str, t_commend *com, int len, int i);

// free
void		free_mem(char **temp);
void		free_job(t_job **job);
void		free_parse(t_job **job, t_info **b_info);
void		free_all(t_commend *com, t_pool *pool);

// signal
void		parent_signal(void);
void		heredoc_signal_handle(int signal);
void		heredoc_signal(void);
void		signal_handle(int signal);
void		set_signal(void);
void		sigint_handle(int signal);
void		sigquit_handle(int signal);
void		set_in_out(int in, int out);

#endif
