/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:54:27 by jacha             #+#    #+#             */
/*   Updated: 2024/10/20 13:47:43 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

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

struct      s_node;
struct      s_commend;

typedef struct  s_pipe
{
    char            **cmd_pool;
    struct s_pipe   *next;
}   t_pipe;

typedef struct  s_commend
{
    char    *cmd;
	int		indx;
    int     s_qoute;
    int     d_qoute;
    int     pipe;
}   t_commend;

int		syntax_check(t_commend *com);
void	qoute_check(int *qoute);

void    tokenizer(t_commend *com);

void	init_t_commend(t_commend *com);

int		is_whitespace(char chr);

#endif
