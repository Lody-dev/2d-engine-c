/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	printer(unsigned long nb)
{
	if (nb >= 16)
	{
		printer(nb / 16);
		nb = nb % 16;
	}
	if (nb < 10)
		ft_putchar(nb + 48);
	else if (nb >= 10 && nb < 16)
		ft_putchar(nb + 87);
}

static int	lenth_counter(unsigned long nb)
{
	unsigned long	n;
	int				i;

	if (nb == 0)
		return (1);
	i = 0;
	n = nb;
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_putptr(unsigned long nb)
{
	int	lenth;

	if (nb == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	lenth = lenth_counter(nb);
	printer(nb);
	return (lenth + 2);
}
