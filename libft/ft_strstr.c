/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:15:37 by sromanet          #+#    #+#             */
/*   Updated: 2016/12/27 14:27:26 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *l)
{
	if (!big && l[0] == '\0')
		return (NULL);
	if (!*big && !*l)
		return ((char *)big);
	while (*big)
		if (!ft_strncmp(big++, l, ft_strlen(l)))
			return ((char *)big - 1);
	return (NULL);
}
