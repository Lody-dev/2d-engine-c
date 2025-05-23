/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:35:13 by viaremko          #+#    #+#             */
/*   Updated: 2025/05/10 17:23:25 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	printer(unsigned int nb)
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

static int	lenth_counter(unsigned int nb)
{
	unsigned int	n;
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

int	ft_puthex(unsigned int nb)
{
	int	lenth;

	lenth = lenth_counter(nb);
	printer(nb);
	return (lenth);
}
