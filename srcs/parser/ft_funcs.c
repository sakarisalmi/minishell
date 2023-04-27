/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:40:57 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/27 15:04:06 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_isspace(char c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strncat(char *dest, const char *src, size_t n);

/*----------------------------------------------------------------------------*/

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v');
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (temp);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// char	*new_strncat(char *dest, const char *src, size_t n)
// {
// 	unsigned int	len_dest;
// 	unsigned int	len_src;

// 	len_dest = ft_strlen(dest);
// 	len_src = ft_strlen(src);
// 	if (len_src < n)
// 		ft_strcpy(&dest[len_dest], src);
// 	else
// 	{
// 		ft_strncpy(&dest[len_dest], src, n);
// 		dest[len_dest + n] = '\0';
// 	}
// 	return (dest);
// }

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(dest);
	len2 = ft_strlen(src);
	if (len2 < n)
		ft_strcpy(&dest[len1], src);
	else
	{
		ft_strncpy(&dest[len1], src, n);
		dest[len1 + n] = '\0';
	}
	return (dest);
}

/*	This function was created to solve the heap-buffer-overflow issues
	that were created by the ft_strncat function. This function simply
	adds the src-char to the end of the dest-string and sets the next
	char as NULL. */
// char	*minishell_strcat(char *dest, const char src_char_to_add)
// {
// 	unsigned int	dest_len;

// 	dest_len = ft_strlen(dest);
// 	dest[dest_len] = src_char_to_add;
// 	dest[dest_len + 1] = '\0';
// 	return (dest);
// }

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (size)
	{
		if (!ptr)
			return (malloc(size));
		new_ptr = malloc(size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, size);
			free(ptr);
		}
	}
	return (new_ptr);
}

// int	main()
// {
// 	t_list	*lst;
// 	char	*src = "add this string to dest";
// 	int		i;

// 	printf("program to fix ft_strncat\n");
// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew(ft_calloc((ft_strlen(src) + 1), sizeof(char))));
// 	i = 0;
// 	while (src[i])
// 	{
// 		ft_strncat(ft_lstlast(lst)->content, &src[i], 1);
// 		printf("src[%i]; dest: %s\n", i, ft_lstlast(lst)->content);
// 		i++;
// 	}
// 	printf("final dest: %s\n", ft_lstlast(lst)->content);
// 	return (0);
// }
