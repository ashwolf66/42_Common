/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_hb.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 06:14:57 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 06:27:38 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HB_H
# define MINISHELL_HB_H

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
# include "minishell_jh.h"

# define VAL_ERR 0

typedef struct s_list
{
	char			*key;
	char			*val;
	struct s_list	*next;
}	t_list;

typedef struct s_info
{
	t_list	*env_list;
	t_list	*exp_list;
	char	**cmd;
	char	**env_arr;
	// char	*promp;
	char	*home;
	char	*pwd;
	char	*old_pwd;
	int		flag;
	int		end_stat;
}			t_info;

// builtin
int		ft_pwd(t_info *b_info);
int		ft_env(t_info *b_info);
int		ft_unset(t_info *b_info);

// ft_cd
int		ft_cd(t_info *b_info);
int		type_check(t_info *b_info);
int		type_tilde(t_info *b_info);
int		type_dash(t_info *b_info);
int		run_cd(t_info *b_info);

// ft_cd_utils
int		cd_valid_check(t_info *b_info);
char	*get_env_val(t_info *b_info, char *key);
void	setting_pwd(t_info *b_info);
void	update_env_val(t_info *b_info, char *list_name, char *key, char *val);

// ft_export
int		ft_export(t_info *b_info);
void	add_union(t_info *b_info, char **key_val, int i);
void	plus_case(t_info *b_info, char **key_val, int flag, int i);
void	equal_case(t_info *b_info, char **key_val, int flag, int i);
void	nothing_case(t_info *b_info, int flag, int i);

// ft_export_utils
int		check_key_format(char *key);
int		exp_valid_check(t_info *b_info, int index);
int		equal_and_plue_search(char *cmd);
void	equal_util(t_list *list_name, char **key_val);
void	plus_util(t_list *list_name, char **key_val);

// ft_echo
int		ft_echo(t_info *b_info);
int		echo_string_check(t_info *b_info);

// ft_exit
int		ft_exit(t_info *b_info);
int		is_numeric(char *str);
void	all_free(t_info *b_info);

// linked_list
t_list	*create_node(char *val);
void	make_list(char **val, t_list **linked_list);
void	add_sorted_node(t_list **head, char *val);
void	add_back_node(t_list **head, char *val);
void	del_node(t_list **head, char *key);

// linked_list_utill
void	print_list(t_list *head, char *cmd);
void	free_list(t_list *head);
int		find_list_key(t_list *head, char *find_cmd);
char	**key_val_separ(char *cmd);

// par_list
char	**update_env_arr(char **env);
void	env_init(t_info *b_info, char **env);
void	list_val_swap(t_list *curruent, t_list *temp);
void	sort_env(t_list *head);
void	sort_exp(t_list *head);

// utils
char	*exp_val(char **key);
// char	*prompt_color(void);
void	free_split(char **split);
void	ft_putstr(char *s);
void	print_err(char *e_mess, char *str);

// ft_error
int		err_cd(t_info *b_info, int type);
int		err_exit(t_info *b_info, int type);
int		err_exp(t_info *b_info, int type);
int		err_env(int type);

#endif
