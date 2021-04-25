#include "../../cub3d.h"
#include "../../libft/libft.h"

void	get_resolution(char *line, int *width, int *height)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	*width = ft_atoi(line + i);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	*height = ft_atoi(line + i);
}
