/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:15:58 by viaremko          #+#    #+#             */
/*   Updated: 2024/09/18 13:38:59 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	memmove_forward(char *d, const char *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	memmove_backward(char *d, const char *s, unsigned int n)
{
	unsigned int	i;

	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	char			*s;
	char			*d;

	s = (char *)src;
	d = (char *)dest;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
		memmove_forward(d, s, n);
	else
		memmove_backward(d, s, n);
	return (dest);
}
