/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:08:57 by oissa             #+#    #+#             */
/*   Updated: 2025/04/16 15:09:12 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

int	ft_strtok_utils(const char *delim, char **start, char **last)
{
	*start = *last;
	while (**last)
	{
		if (is_delim(**last, delim))
		{
			**last = '\0';
			(*last)++;
			if (*start == *last)
			{
				(*start)++;
				continue ;
			}
			return (EXIT_FAILURE);
		}
		(*last)++;
	}
	return (EXIT_SUCCESS);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*start;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	start = last;
	if (ft_strtok_utils(delim, &start, &last) == EXIT_FAILURE)
		return (start);
	last = NULL;
	if (start == last)
		return (NULL);
	return (start);
}
