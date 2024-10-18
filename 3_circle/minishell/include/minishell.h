/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:27:39 by jacha             #+#    #+#             */
/*   Updated: 2024/09/28 12:41:27 by jacha            ###   ########.fr       */
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

typedef struct  s_node
{
    char            **cmd_pool;
    struct s_node   *next;
}   t_node;

typedef struct  s_commend
{
    char    *cmd;
    int     s_quote;
    int     d_qoute;
    int     pipe;
}   t_commend;

int syntax_check(t_commend comme);

#endif
