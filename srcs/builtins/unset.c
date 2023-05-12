/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:32:29 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/05 16:32:32 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	unset(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i++])
	{
		while (*envs++)
		{
			if (ft_strncmp(*envs, args[i], ft_strlen(args[i])) == 0)
			{
				while (envs[j])
				{
					envs[j] = envs[j +1];
					j++;
				}
				break ;
			}
		}
	}
	return (0);
}
