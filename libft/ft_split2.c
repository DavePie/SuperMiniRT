/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:48 by dvandenb          #+#    #+#             */
/*   Updated: 2023/11/21 07:55:37 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_strs(const char *str, char *split)
{
	int	prev_char;
	int	cur_char;
	int	total;

	total = 0;
	prev_char = 1;
	while (*str)
	{
		cur_char = ft_strchr(split, *str++) != 0;
		if (!cur_char && prev_char)
			total++;
		prev_char = cur_char;
	}
	return (total);
}

static char	*get_word(const char *str, char *split, int *j)
{
	int		i;
	char	*ans;

	i = 0;
	while (str[i] && !ft_strchr(split, str[i]))
		i++;
	ans = (char *)malloc(sizeof(*ans) * (i + 1));
	if (!ans)
		return (0);
	*j = i;
	ans[i] = '\0';
	while (--i >= 0)
		ans[i] = str[i];
	return (ans);
}

static char	**free_arr(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	return ((char **)(0));
}

char	**ft_split2(char const *str, char *split)
{
	int		total;
	char	**ans;
	int		i;
	int		j;

	i = 0;
	total = count_strs(str, split);
	ans = (char **)malloc(sizeof(*ans) * (total + 1));
	if (!ans)
		return (0);
	while (*str)
	{
		j = 1;
		if (!ft_strchr(split, *str))
		{
			ans[i] = get_word(str, split, &j);
			if (!ans[i++])
				return (free_arr(ans, i - 2));
		}
		str += j;
	}
	ans[i] = 0;
	return (ans);
}
