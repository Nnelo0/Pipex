/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebroudic <ebroudic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:28:40 by ebroudic          #+#    #+#             */
/*   Updated: 2024/10/22 15:41:55 by ebroudic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c)
		|| ('0' <= c && '9' >= c))
		return (1);
	return (0);
}
/*int main()
{
	ft_isalnum(4);
	return (0);
}*/