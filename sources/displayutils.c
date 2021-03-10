#include "../cub3d.h"

int 	display_keycode(int keycode, data_t *data)
{
	printf("%d\n", keycode);
}

int 	display_button(int button, int x, int y, data_t *data)
{
	printf("press: %d, x: %d, y: %d\n", button, x, y);
}

int 	display_buttonrelease(int button, int x, int y, data_t *data)
{
	printf("release: %d, x: %d, y: %d\n", button, x, y);
}

void	displaymaparray(map_t *map)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	printf("map:\n");
	while(i < 8)
	{
		j = 0;
		while (j++ < 8)
		{
			printf("%d, ", map->map[k]);
			k++;
		}
		printf("\n");
		i++; 
	printf("\n");
	}
}
