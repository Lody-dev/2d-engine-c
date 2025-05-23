/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:38:56 by viaremko          #+#    #+#             */
/*   Updated: 2024/09/20 11:17:47 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, unsigned int len)
{
	unsigned int	i;
	unsigned int	little_len;
	unsigned int	j;

	i = 0;
	little_len = 0;
	if (*little == '\0')
		return ((char *)big);
	if (*big == '\0')
		return (0);
	while (little[little_len] != '\0')
		little_len++;
	while (i + little_len <= len)
	{
		j = 0;
		while (big[j + i] == little[j])
		{
			j++;
			if (j == little_len)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
