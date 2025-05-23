/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:21:51 by viaremko          #+#    #+#             */
/*   Updated: 2024/10/08 18:21:57 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_next_word_length(const char *s, int *i, char c)
{
	int	wlen;

	wlen = 0;
	while (s[*i] == c && s[*i] != '\0')
		(*i)++;
	while (s[*i] != c && s[*i] != '\0')
	{
		wlen++;
		(*i)++;
	}
	return (wlen);
}

void	free_allocated_memory(char **ptr, int pos)
{
	while (pos > 0)
	{
		free(ptr[pos - 1]);
		pos--;
	}
}

int	f_fillmemory(char **ptr, const char *s, char c)
{
	int	pos;
	int	i;
	int	wlen;

	pos = 0;
	i = 0;
	while (s[i] != '\0')
	{
		wlen = get_next_word_length(s, &i, c);
		if (wlen > 0)
		{
			ptr[pos] = malloc(wlen + 1);
			if (!ptr[pos])
			{
				free_allocated_memory(ptr, pos);
				return (-1);
			}
			ptr[pos][wlen] = '\0';
			ft_strlcpy(ptr[pos], s + i - wlen, wlen + 1);
			pos++;
		}
	}
	return (0);
}

int	f_wcnt(const char *s, const char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			wcount++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (wcount);
}

char	**ft_split(const char *s, const char c)
{
	int		wcount;
	char	**ptr;

	wcount = f_wcnt(s, c);
	ptr = malloc((wcount + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	if (f_fillmemory(ptr, s, c) == -1)
	{
		free(ptr);
		return (NULL);
	}
	ptr[wcount] = NULL;
	return (ptr);
}
