/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:44:57 by viaremko          #+#    #+#             */
/*   Updated: 2024/10/07 20:37:12 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	a_mem(int n)
{
	int	box;

	if (n == 0)
		return (1);
	box = 0;
	while (n)
	{
		n /= 10;
		box++;
	}
	return (box);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long int	num;
	int			box;

	num = n;
	box = a_mem(num);
	if (n < 0)
	{
		num = -num;
		box++;
	}
	ptr = (char *)malloc(box + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[box] = '\0';
	while (box > 0)
	{
		box--;
		ptr[box] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
