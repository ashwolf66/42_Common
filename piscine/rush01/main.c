/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:23:02 by yonan             #+#    #+#             */
/*   Updated: 2024/01/23 18:30:42 by yonan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern int	get_view_info(int info[16], char *src);
extern int	find_case(int table[4][4], int info[16], int depth);
extern int	print_error(void);

int	main(int argc, char *argv[])
{
	int	info[16];
	int	table[4][4];

	if (argc != 2)
	{
		print_error();
		return (0);
	}
	if (!get_view_info(info, argv[1]) || !find_case(table, info, 0))
	{
		print_error();
		return (0);
	}
	return (0);
}
