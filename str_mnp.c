#include "cube.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	ret = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
	{
		free (ret);
		return (NULL);
	}
	if (s1)
		while (s1[++i])
			ret[j++] = s1[i];
	i = 0;
	if (s2)
		while (s2[i])
			ret[j++] = s2[i++];
	ret[j] = '\0';
	return (ret);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_strchr(char s, char *scan)
{
	int	i;

	i = 0;
	while (scan[i] && scan[i] != s)
		i++;
	if (i == ft_strlen(scan))
		return (0);
	return (1);
}

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	p = NULL;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	p = malloc((i + 1) * sizeof(char));
	if (!(p))
		return (NULL);
	while (i > 0)
	{
		p[j] = src[j];
		j++;
		i--;
	}
	p[j] = '\0';
	return (p);
}
