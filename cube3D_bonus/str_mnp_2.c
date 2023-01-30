/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_mnp_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:11:45 by sfarhan           #+#    #+#             */
/*   Updated: 2023/01/30 19:22:10 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*f;

	if (length == 0)
	{
		return (0);
	}
	s = (unsigned char *)second;
	f = (unsigned char *)first;
	i = 0;
	while ((f[i] != '\0' || s[i] != '\0') && (f[i] == s[i]) && (i < length - 1))
	{
		i++;
	}
	return (f[i] - s[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static int	ftskip(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	return (i);
}

static int	ft_signe(char *str, int i)
{
	unsigned long long	resultat;

	resultat = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - '0');
		if (resultat > LLONG_MAX)
			return (-1);
		i++;
	}
	return (resultat);
}

int	ft_atoi(char *str)
{
	int					i;
	int					a;
	unsigned long long	resultat;

	i = ftskip(str);
	a = 1;
	resultat = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	if (ft_signe(str, i) == -1)
		return (-1);
	else
		resultat = ft_signe(str, i) * a;
	return (resultat);
}
