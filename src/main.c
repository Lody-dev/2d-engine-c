#include "../lib/libft/libft.h"

typedef struct
{
	char** map;
	int height;
	int width;
}map;

map read_map(map m)
{
	int		fd;
	char	*line;
	fd = open("map", O_RDONLY);
	if (fd == -1)
		exit(-1);
	else
	{
		while ((line = get_next_line(fd)) != NULL)
		{
			if(m.width < (int)ft_strlen(line))
				m.width = ft_strlen(line);
			m.height++;	
			free(line);
		}
		free(line);
	}
	close(fd);
	ft_printf("H:%d\nW:%d\n", m.height, m.width);
	return (m);
}

char** map_init(map dimentions)
{
	char** map_malloc = malloc(dimentions.height * sizeof(char *));
	return(map_malloc);
}

int map_copy(char** map)
{
	int		fd;
	char	*line;
	int	i;
	fd = open("map", O_RDONLY);
	i = 0;
	if (fd == -1)
		return(-1);
	else
	{
		while ((line = get_next_line(fd)) != NULL)
		{
			map[i] = line;
			i++;
		}
	}
	close(fd);
	return (1);
}

void print_map(char **map, int height, int width) {
    // Iterate over each row
    for (int i = 0; i < height; i++) {
        // Print each string in the row (each map[i] is a string)
        for (int j = 0; j < width; j++) {
            // Print the character at map[i][j]
            ft_putchar(map[i][j]);
        }
    }
}

int wall_check(map data)
{
	//Last character is indeed a '/n', so read and check untill pre-last char.
	//Width - 2 to get the last 1 index.
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < data.width - 2)
	{
		if(data.map[0][i] != '1' && data.map[data.height-1][i] != '1')
			return(-1);
		i++;
	}
	while(j < data.height - 1)
	{
		if(data.map[j][0] != '1' && data.map[j][data.width - 2] != '1')
			return(-1);
		j++;
	}
	return(1);
}

int main()
{
	map dimensions = {NULL,0,0};
	dimensions = read_map(dimensions);
	dimensions.map = map_init(dimensions); 
	if(0 < map_copy(dimensions.map))
		ft_printf("Map stored succesfully!\n");
	else
		ft_printf("Map copy falied!\n");
	//print_map(dimensions.map, dimensions.height, dimensions.width);
	if(wall_check(dimensions) == -1)
		return(2); //to check exit status "echo $?"
	return(0);
}
