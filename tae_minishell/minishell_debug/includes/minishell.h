/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:21:29 by taejikim          #+#    #+#             */
/*   Updated: 2024/06/17 13:02:09 by taejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libms.h"

typedef struct s_envp
{
	char	*key;
	char	*value;
}	t_envp;

typedef struct s_vector
{
	void	**data;
	size_t	size;
	size_t	capacity;
}	t_vector;

typedef struct s_token
{
	int		type;
	char	*chunk;
}	t_token;

typedef struct s_info
{
	t_token		*token;
	char		*temp;
	t_vector	*chunk;
	t_vector	tokens;
	size_t		idx;
	int			state;
	int			prev_t;
}	t_info;

typedef struct s_input
{
	char		*line;
	char		*output;
	int			state;
	t_vector	*vector;
	t_info		info;
}	t_input;

typedef struct s_file
{
	int		type;
	char	*io_target;
}	t_file;

typedef struct s_job
{
	t_vector	*infiles;
	t_vector	*outfiles;
	t_vector	*arg;
	char		*cmd;
	bool		is_builtin;
}	t_job;

typedef struct s_mj
{
	t_job	*job;
	t_token	*tok;
}	t_mj;

typedef struct s_seq
{
	t_vector	*path;
	t_vector	*dic;
	t_vector	*jobs;
	bool		single_cmd_mode;
}	t_seq;

typedef struct s_system
{
	t_input		input;
	bool		need_pair;
	char		*backup;
	char		*prompt;
	t_seq		seq;	
}	t_system;

# define NUM_OF_BUILT_IN 5
# define ERR_FRONT_END 0
# define NONE 0b000000000000000000000
# define UNQUOTED 0b000000000000100000000
# define QUOTED 0b000000000001000000000
# define STAT_OPR 0b000000000010000000000
# define STAT_ORD 0b000000000100000000000
# define ERR_SYN 0b000000001000000000000
# define ERR_PAIR 0b000000010000000000000
# define STAT_QUOTE 0b000000100000000000000
# define STAT_UNQUOTE 0b000001000000000000000
# define STAT_SQUOTED 0b000010000000000000000
# define STAT_NORMAL 0b000100000000000000000
# define RELATIVE_PATH 0b001000000000000000000
# define ABSOLUTE_PATH 0b010000000000000000000
# define PURE_PATH 0b100000000000000000000
# define MASK_OPERAND 0b0000000001000000
# define MASK_CMD 0b0000000011000000
# define FLAG_CMD 0b0000000001000000
# define FLAG_BUILTIN 0b0000000010000000
# define MASK_OPERATOR 0b0000000000111111
# define MASK_REDIR 0b0000000000001111
# define FLAG_NEW_LINE 0b0000000000100000
# define FLAG_PIPE 0b0000000000010000
# define FLAG_IN_REDIR 0b0000000000001000
# define FLAG_HERE_DOC 0b0000000000000100
# define FLAG_OUT_REDIR 0b0000000000000010
# define FLAG_OUT_REDIR_APP 0b0000000000000001

void		ms_check_pipe_pair_recur(
				t_vector *toks, int idx, int *stat, int prev);
void		ms_check_quote_recur(t_vector *toks, int idx, int *stat);
int			ms_detect_parse_err(t_vector *toks);
bool		ms_front_end(t_system *system);
void		ms_get_chunks(t_vector *chunks, char **input, char **output);
void		ms_pipeline_expansion(t_system *system);
void		ms_init_job(t_job *job);
bool		ms_pipeline_detect_err(t_system *system);
bool		ms_pipeline_parse(t_system *system);
void		ms_pipeline_tokenize(t_system *system);
bool		ms_post_process(t_seq *seq);
void		_post_process_print_err(const char *str);
int			_check_path_dir(t_job *job);
bool		_post_process_check_builtin(t_job *job);
char		*ms_readline(const char *prompt);
void		ms_remove_quote(t_vector *toks);
void		ms_sh_param_expan(t_vector *toks, t_vector *dic);
bool		ms_cal_quote_stat(char chr);
char		*ms_search_value(t_vector *dic, char *key);
char		*ms_strdup_to_key(char *input, size_t *real_idx);
bool		ms_isalnum_und(char chr);
void		ms_reset_system(t_seq *seq);
void		ms_init_system(
				t_system *system, int argc, char **argv, char **envp);
void		ms_tokenizer(t_info *info);
void		ms_init_info(t_info *info, t_vector *chunk);
void		ms_check_syntax(int *state, int prev_t, int current_t);
int			ms_scan_type(char *chunk);
t_token		*ms_init_token(t_token *token);
void		ms_clean_blank(t_vector *vector);
bool		ms_is_set(char chr, char *set);
void		ms_exit(int status, char *msg, int out_chan);
void		ms_detect_exit(const char *input);
void		ms_collec_mem(void *mem);
void		ms_clear_mem(void);
void		ms_init_input(t_input *input);
void		ms_init_seq(t_seq *seq, char **envp);
int			ms_print_syntax_err(t_input *input);
void		ms_make_dic(char **envp, t_vector *dic, int idx);
void		ms_split_cmd(char **input, char **output, char pair, int state);
int			ms_is_redir(char *output);
void		ms_handle_none(char **input, char **output, char *pair, int *state);
void		ms_handle_unquoted(
				char **input, char **output, char *pair, int *state);
void		ms_handle_quoted(
				char **input, char **output, char pair, int *state);

t_vector	*ms_vector_create(void);
void		ms_vector_resize(t_vector *vector, size_t new_capacity);
void		ms_vector_add(t_vector *vector, void *item);
void		ms_vector_remove(t_vector *vector, size_t index);
void		*ms_vector_get(t_vector *vector, size_t index);
char		*_sh_param_expan(char *chunk, t_vector *dic);
void		ms_pipeline_expansion(t_system *system);
void		ms_init_job(t_job *job);
t_job		*ms_make_job(t_vector *toks, int *idx);
bool		_post_process_check_path(t_seq *seq);
void		_post_process_check_single_cmd(t_seq *seq);
bool		_post_process_check_builtin(t_job *job);
int			_check_path_dir(t_job *job);
void		_post_process_print_err(const char *str);
int			_post_process_join_path(t_job *job, t_vector *path);

void		ms_print_vec(t_vector *vector);
void		ms_print_token(t_vector *tokens, size_t dst);
void		ms_print_dic(t_vector *dic);
void		ms_print_parse_result(t_system *system);

#endif
