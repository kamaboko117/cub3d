#include "../../cub3d.h"
#include "../../libft/libft.h"

int	isempty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n'
			&& line[i] != '\t' && line[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	isdirection(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

int	isrow(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (!ft_isdigit(row[i]) && !isdirection(row[i]) && row[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
