/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:35:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/21 17:06:37 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

# define OUT_BUF (size_t)100000

# define FLAG_MIN 0x1
# define FLAG_L 0x2
# define FLAG_R 0x4
# define FLAG_RR 0x8
# define FLAG_A 0x10
# define FLAG_T 0x20
# define FLAG_GG 0x40
# define FLAG_P 0x80
# define FLAG_S 0x100
# define FLAG_U 0x200
# define FLAG_F 0x400
# define FLAG_D 0x800
# define FLAG_G 0x1000
# define FLAG_SS 0x2000
# define FLAG_C 0x4000
# define FLAG_N 0x8000

# define ST_NEW() stack_init()
# define ST_ADD(x, data) x->add(x, data)
# define ST_SORT(x, f) x->sort(x, f)
# define ST_DEL(x) x = x->del(x)
# define ST_ITER(x, f, param, rev) x->iter(x, f, param, rev)

typedef struct	s_plist
{
	void			*data;
	size_t			num;
	struct s_plist	*next;
	struct s_plist	*prev;
}				t_plist;

typedef struct	s_stack
{
	t_plist				*list;
	size_t				counter;
	void				(*add)(struct s_stack *, void *data);
	void				(*iter)(struct s_stack *, void (*f)(void *, void *),
													void *param, int reverse);
	void				(*sort)(struct s_stack*, int (*f)(void *, void *));
	struct	s_stack		*(*del)(struct s_stack *);
}				t_stack;

typedef struct		s_file
{
	char			*name;
	struct stat		info;
	DIR				*dir;
}					t_file;

void				*ft_xmalloc(size_t size);
void				del_files(t_file *file, void *null);

t_stack				*get_args(int *flags,  int argc, char **argv);
void				print_err(char *dirname);

void				print_files(t_stack *files, int flags);
void				print_dir(t_file *file, int *flags);

t_stack				*stack_init();
void				*files_sort(int flags);
void				st_sort(t_stack *me, int (*f)(void *, void *));

void				buf_add(char *str, size_t size);

#endif
