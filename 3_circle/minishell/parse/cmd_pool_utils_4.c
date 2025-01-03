/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pool_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <jacha@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 09:04:17 by jacha             #+#    #+#             */
/*   Updated: 2024/12/31 09:05:36 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jh.h"
#include "minishell_hb.h"

void	ms_c_quote_check(char *src, int i, t_commend *com)
{
	if (src[i] == '\'' && com->d_quote == 0)
		com->s_quote = !com->s_quote;
	else if (src[i] == '"' && com->s_quote == 0)
		com->d_quote = !com->d_quote;
}

void	ms_strlcpy_2(char *src, char *dest, size_t *i, size_t *j)
{
	if (*i > 0 && (src[*i] == '<' || src[*i] == '>')
		&& src[*i] != src[*i - 1]
		&& !is_whitespace(src[(*i) - 1]))
		dest[(*j)++] = ' ';
	if (*i > 0 && src[*i] != '<' && src[*i] != '>'
		&& !is_whitespace(src[*i]) && (src[(*i) - 1] == '<'
			|| src[(*i) - 1] == '>'))
		dest[(*j)++] = ' ';
}

void	ms_strlcpy_3(char *src, char *dest, size_t *i, size_t *j)
{
	if (src[*i] == ' ' && src[(*i) + 1] == '\0')
		dest[(*j)++] = '\0';
	else if (src[*i] == '\0')
		dest[(*j)++] = '\0';
	else
		dest[(*j)++] = src[(*i)++];
}
