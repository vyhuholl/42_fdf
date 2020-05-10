/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghezn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:37:49 by sghezn            #+#    #+#             */
/*   Updated: 2019/04/09 15:51:09 by sghezn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_sign(int *n, int *sign)
{
	if (*n < 0)
	{
		*n *= -1;
		*sign = 1;
	}
}

char		*ft_itoa(int n)
{
	int		len_counter;
	int		sign;
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 2;
	sign = 0;
	ft_get_sign(&n, &sign);
	len_counter = n;
	while (len_counter /= 10)
		len++;
	len += sign;
	if (!(res = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	res[--len] = '\0';
	while (len--)
	{
		res[len] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}
