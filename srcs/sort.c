/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:32 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/14 16:44:19 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

void	quick_sort_list(t_file *start, t_file *left, t_file *right,
									int (*f)(t_file *left, t_file *right))
{
	t_file	*p;
	t_file	*i;
	t_file	*j;

	i = left;
	j = right;
	while (i != j)
	{
		if (f(i, j) > 0 == (i->fromstart < j->fromstart))
		{
			start = file_swap(start, i, j);
			p = i;
			i = j;
			j = (p->fromstart < j->fromstart) ? p->next : p->prev;
		}
		else
			j = (i->fromstart < j->fromstart) ? j->prev : j->next;
	}
	if (left->fromstart < i->fromstart - 1)
		quick_sort_list(start, left, i->prev, f);
	if (i->next->fromstart < right->fromstart)
		quick_sort_list(start, i->next, right, f);
}

static void		ptr_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	quick_mas_sort(char **mas, int left, int right)
{
	int		i;
	int		j;
	int		p;
	char	*tmp[100];

	i = left;
	j = right;
	while (i != j)
	{
		if((ft_strcmp(mas[i], mas[j]) > 0) != (i > j))
		{

			//ptr_swap(&mas[i], &mas[j]);
			tmp[i] = mas[i];
			mas[i] = mas[j];
			mas[j] = tmp[i];

			p = i;
			i = j;

			j = (p < j) ? p++ : p--;
		}
		else
			j = (i < j) ? j - 1 : j + 1;
	};
	if (left < i - 1)
		quick_mas_sort(mas, left, i - 1);
	if (i + 1 < right)
		quick_mas_sort(mas,i + 1, right);
}
