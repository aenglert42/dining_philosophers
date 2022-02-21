#include "philo.h"

static int	static_ft_convert(const char *str, int i, int sign)
{
	int		n;

	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((n == 2147483647 / 10 && str[i] - '0' == 7) && sign == 1)
			return (2147483647);
		if ((n == 2147483648 / 10 && str[i] - '0' == 8) && sign == -1)
			return (-2147483648);
		if (n > 2147483647 / 10 || (n == 2147483647 / 10 && str[i] - '0' > 7))
		{
			if (sign == 1)
			{
				return (-1);
			}
			else
			{
				return (0);
			}
		}
		n = 10 * n + (str[i++] - '0');
	}
	return (n * sign);
}

int	philo_atoi(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1 - 2 * (str[i++] == '-');
	}
	return (static_ft_convert(str, i, sign));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static bool	static_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}

bool	is_positive_number(char *str)
{
	int	i;
	int	len;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (!static_isdigit(str[i]))
			return (false);
		i++;
	}
	len = ft_strlen(str);
	if (len == 0 || i < len)
		return (false);
	return (true);
}
