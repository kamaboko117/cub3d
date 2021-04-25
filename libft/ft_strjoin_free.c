#include "libft.h"
#include <stdlib.h>

void	ft_strjoin_free(char **str, char *buf)
{
	char	*tmp;

	if (*str == NULL)
		*str = ft_strdup(buf);
	else if (**str == '\0')
	{
		free(*str);
		*str = ft_strdup(buf);
	}
	else
	{
		tmp = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(tmp, buf);
		free(tmp);
	}
}