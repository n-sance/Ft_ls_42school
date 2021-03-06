/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:08:49 by sschmele          #+#    #+#             */
/*   Updated: 2019/07/05 14:16:36 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

void		ft_stradd_nb(char *s, long nb)
{
	int		i;
	int		a;
	char	*main;

	i = -1;
	a = 1;
	main = "0123456789";
	if (nb == 0)
		s[0] = 0 + '0';
	else
	{
		if (nb < 0)
		{
			s[++i] = '-';
			nb *= -1;
		}
		while (a <= nb / 10)
			a *= 10;
		while (nb)
		{
			s[++i] = main[(nb / a) % 10];
			nb %= a;
			a /= 10;
		}
	}
}

void		buf_add_num(unsigned int n)
{
	int		a;
	long	res;
	char	ch[1];

	a = 1;
	res = n;
	if (res < 0)
	{
		res *= -1;
		ft_putchar('-');
	}
	while (a <= res / 10)
		a *= 10;
	while (a != 0)
	{
		*ch = res / a + '0';
		buf_add(ch, 1);
		res = res % a;
		a = a / 10;
	}
}

int			file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

void		fill_type(t_file *file)
{
	if (S_ISDIR(file->info.st_mode))
		file->type = 'd';
	else if (S_ISBLK(file->info.st_mode))
		file->type = 'b';
	else if (S_ISCHR(file->info.st_mode))
		file->type = 'c';
	else if (S_ISFIFO(file->info.st_mode))
		file->type = 'p';
	else if (S_ISLNK(file->info.st_mode))
		file->type = 'l';
	else if (S_ISREG(file->info.st_mode))
		file->type = '-';
	else if (S_ISSOCK(file->info.st_mode))
		file->type = 's';
}
