/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/21 17:06:43 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_file *file, int *flags)
{
	char		*name;

	name = ft_strrchr(file->name, '/');
	buf_add(name ? name + 1 : file->name, ft_strlen(name ? name + 1 : file->name));
	buf_add("\n", 1);
	// ft_putendl(name ? name + 1 : file->name);
}

void			print_files(t_stack *files, int flags)
{
	ST_ITER(files, (void (*)(void *, void *))print_file, &flags, flags & FLAG_R);
}
