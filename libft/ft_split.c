/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:48 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/13 11:29:46 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_strs(const char *str, char c)
{
	int	prev_char;
	int	cur_char;
	int	total;

	total = 0;
	prev_char = 1;
	while (*str)
	{
		cur_char = *str++ == c;
		if (!cur_char && prev_char)
			total++;
		prev_char = cur_char;
	}
	return (total);
}

static char	*get_word(const char *str, char c, int *j)
{
	int		i;
	char	*ans;

	i = 0;
	while (str[i] && str[i] != c)
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

char	**ft_split(char const *str, char c)
{
	int		total;
	char	**ans;
	int		i;
	int		j;

	i = 0;
	total = count_strs(str, c);
	ans = (char **)malloc(sizeof(*ans) * (total + 1));
	if (!ans)
		return (0);
	while (*str)
	{
		j = 1;
		if (*str != c)
		{
			ans[i] = get_word(str, c, &j);
			if (!ans[i++])
				return (free_arr(ans, i - 2));
		}
		str += j;
	}
	ans[i] = 0;
	return (ans);
}
