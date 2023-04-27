/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:51:24 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/26 16:18:08 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		**str_array_add_str(char **str_array, char *new_str);
char		**str_array_remove_str_by_index(char **str_array, int index);
static char	**str_array_rem_helper_func(char **str_array, int *size, int index);

/*----------------------------------------------------------------------------*/

/*	This function re-creates a new string array based on an older string array.
	The function adds a new string into an array of strings
	that ends in a NULL pointer.

	This function mallocs a new string array (that is one size larger than
	the old str_array), sets the strings pointers to those of old array,
	adds the new given string to the end and sets the last string pointer as NULL.
	We free the old string array and return the new one. */
char	**str_array_add_str(char **str_array, char *new_str)
{
	char	**new_str_array;
	int		size;
	int		i;

	size = 0;
	while (str_array[size])
		size++;
	new_str_array = malloc((size + 2) * sizeof(char *));
	if (!new_str_array)
		return (NULL);
	i = -1;
	while (++i < size)
		new_str_array[i] = str_array[i];
	free (str_array);
	new_str_array[i] = new_str;
	new_str_array[i + 1] = NULL;
	return (new_str_array);
}

/*	This function re-creates the given string-array by making it one
	element shorter. The string-array ends in a NULL-pointer.
	
	This function mallocs a new string array (that is one size smaller than
	the old str_array), sets the strings pointers to those of old array,
	removes (and frees) the given index.
	We free the old string array and return the new one. */
char	**str_array_remove_str_by_index(char **str_array, int index)
{
	char	**new_str_array;
	int		size;
	int		i;
	int		j;

	size = 0;
	new_str_array = str_array_rem_helper_func(str_array,
			&size, index);
	if (size == -1)
		return (str_array);
	if (!new_str_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != index)
			new_str_array[j++] = str_array[i];
		else
			free(str_array[i]);
		i++;
	}
	new_str_array[j] = NULL;
	return (new_str_array);
}

static char	**str_array_rem_helper_func(char **str_array, int *size,
	int index)
{
	while (str_array[*size])
		*size += 1;
	if (*size == 0 || index >= *size)
	{
		*size = -1;
		return (NULL);
	}
	return (ft_calloc(*size, sizeof(char *)));
}
