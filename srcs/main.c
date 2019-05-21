/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/21 17:03:07 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"

void			del_files(t_file *file, void *null)
{
	if (file)
	{
		if (file->name)
			free(file->name);
		if (file->dir)
			closedir(file->dir);
		free(file);
	}
}

static void		check_arg(t_file *file, t_stack *params)
{
	t_stack		*dirs;
	t_stack		*files;

	files = params->list->data;
	dirs = params->list->next->data;
	if (!stat(file->name, &file->info))
	{
		if (file->info.st_mode & S_IFDIR)
			ST_ADD(dirs, file);
		else
			ST_ADD(files, file);
	}
	else
		print_err(file->name);
}

static void		throw_args(t_stack *args, t_stack *params, int flags)
{
	t_stack		*files;
	t_stack		*dirs;

	files = params->list->data;
	dirs = params->list->next->data;
	params->counter = flags;
	ST_ITER(args, (void (*)(void *, void *))check_arg, params, flags & FLAG_R);
	if (dirs->list && args->list->data != args->list->next->data)
		flags |= FLAG_N;
	print_files(files, flags);
	ST_ITER(dirs, (void (*)(void *, void *))print_dir, &flags, flags & FLAG_R);
	ST_ITER(args, (void (*)(void *, void *))del_files, NULL, 0);
	ST_DEL(files);
	ST_DEL(dirs);
	ST_DEL(args);
}

int				main(int argc, char **argv)
{
	int			flags;
	t_stack		*args;
	t_file		file;
	t_stack		*params;

	params = ST_NEW();
	ST_ADD(params, ST_NEW());
	ST_ADD(params, ST_NEW());
	flags = 0;
	if ((args = get_args(&flags, argc, argv)))
		throw_args(args, params, flags);
	else
	{
		file.name = ft_strdup(".");
		stat(".", &file.info);
		print_dir(&file, &flags);
		free(file.name);
		closedir(file.dir);
	}
	ST_DEL(params);
	buf_add(NULL, 0);
	return (0);
}
