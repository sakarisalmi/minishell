/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:34:48 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 18:25:37 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_int_val_to_zero(int *a, int *b);
static int		find_word_amount(char const *s, char c);
static int		*find_word_indexes(char const *s, char c, int word_amount);
static void		split_into_strings(char **str_array, const char *s,
					char c, int word_amount);

char	**ft_split(char const *s, char c)
{
	int				i;
	int				word_amount;
	char			**str_array;

	if (!s)
		return (NULL);
	set_int_val_to_zero(&i, &word_amount);
	word_amount = find_word_amount(s, c);
	str_array = (char **)malloc((word_amount + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	if (word_amount != 0)
		split_into_strings(str_array, s, c, word_amount);
	str_array[word_amount] = NULL;
	return (str_array);
}

static int	find_word_amount(char const *s, char c)
{
	int	word_amount;
	int	i;

	i = 0;
	word_amount = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{	
		if (i != 0 && s[i] == c && s[i - 1] != c)
			word_amount++;
		i++;
	}
	if (s[ft_strlen(s) - 1] != c)
			word_amount++;
	return (word_amount);
}

static int	*find_word_indexes(char const *s, char c, int word_amount)
{
	int	i;
	int	j;
	int	*word_idx;
	int	start;

	set_int_val_to_zero(&i, &j);
	start = 1;
	word_idx = (int *)malloc(sizeof(int) * (word_amount * 2));
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c && start == 1)
		{
			word_idx[j++] = i;
			start = 0;
		}
		if (s[i] == c && start == 0)
		{
			word_idx[j++] = i;
			start = 1;
		}
		i++;
	}
	if (start == 0)
		word_idx[j] = i;
	return (word_idx);
}

static void	split_into_strings(char **str_array, const char *s,
		char c, int word_amount)
{
	int	i;
	int	j;
	int	*word_idx;

	j = 0;
	i = 0;
	word_idx = find_word_indexes(s, c, word_amount);
	while (i < word_amount * 2)
	{
		str_array[j++] = ft_substr(s, word_idx[i],
				word_idx[i + 1] - word_idx[i]);
		i += 2;
	}
	free(word_idx);
}

static void	set_int_val_to_zero(int *a, int *b)
{
	*a = 0;
	*b = 0;
}
