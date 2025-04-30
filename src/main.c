#include "../lib/libft/libft.h"

typedef struct
{
	char** map;
	int height;
	int width;

	int coins;
	int player;
	int exit;

	int p_x;
	int p_y;
	
	int cur_exit;
	int cur_coins;
}map;

map map_read_check(map m, char* name)
{
	int		fd;
	char	*line;
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Can't find \"%s\"\n", name);		
		exit(-1);
	}
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

int map_copy(char** map, char* name)
{
	int		fd;
	char	*line;
	int	i;
	fd = open(name, O_RDONLY);
	i = 0;
	if (fd == -1)
	{
		ft_printf("Can't find %s\n", name);		
		return(-1);
	}
	else
	{
		while ((line = get_next_line(fd)) != NULL)
		{
			map[i] = line;
			i++;
		}
	}
	close(fd);
	ft_printf("Map stored succesfully!\n");
	return (1);
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
	ft_printf("Walls: OK!\n");
	return(1);
}

int extention_check(int argc, char** argv)
{
	if(argc != 2)
	{
		ft_printf("Usage: ./Game map.ber\n");
    		return(-1);
	}
	int count = strlen(argv[1]);
	if(ft_strncmp(&argv[1][count-4],".ber",4) == 0)
	{
		ft_printf("Correct extention\n");
		return(0);
	}
	printf("Incorrect extention\n");
	return( -1);
}

int content_check(map *data)
{
	int i;
	int j;

	i = 0;
	while(++i < (data->height - 1))
	{
		j = 0;
		while(++j < (data->width - 2))
		{
			if(data->map[i][j] == '0' || data->map[i][j] == '1')
				continue;
			else if(data->map[i][j] == 'c')
				data->coins = data->coins + 1;
			else if(data->map[i][j] == 'p')
				data->player = data->player + 1;
			else if(data->map[i][j] == 'e')
				data->exit = data->exit + 1;
			else
				return(-1);
		}
	}	
	if(data->exit > 1 || data->player > 1 || data->coins < 1)
		return(-1);
	ft_printf("Content: OK!\nCoins: %d\nPlayer: %d\nExit: %d\n", data->coins, data->player, data->exit);
	return(0);
}
void get_player_position(map* data)
{
	int i;
	int j;

	i = 0;
	while(++i < (data->height - 1))
	{
		j = 0;
		while(++j < (data->width - 2))
		{
			if(data->map[i][j] == 'p')
			{			
				data->p_x = j;
				data->p_y = i;
			}
		}
	}
	ft_printf("Player position: X -> %d   Y -> %d\n", data->p_x, data->p_y);	
}

int reachable_check(map* data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->height || y >= data->width)
		return -1;
	if (data->map[x][y] == '1')
		return -2;
	if (data->cur_coins == data->coins && data->cur_exit == 1)
        	return 1;

	if (data->map[x][y] == 'c')
        	data->cur_coins++;
	
	if (data->map[x][y] == 'e')
		data->cur_exit++;
//	data->map[x][y] = '1';  
	if (reachable_check(data, x + 1, y) == 1) return 1;
	if (reachable_check(data, x - 1, y) == 1) return 1;
	if (reachable_check(data, x, y + 1) == 1) return 1;
	if (reachable_check(data, x, y - 1) == 1) return 1;	
	return -3;
}

int main(int argc, char** argv)
{
	if(extention_check(argc, argv) == -1)
		return(1);
	map dimensions = {NULL,0,0,0,0,0,0,0,0,0};
	dimensions = map_read_check(dimensions, argv[1]);
	dimensions.map = map_init(dimensions); 
	if(map_copy(dimensions.map, argv[1]) == -1)
		return(2);
	if(wall_check(dimensions) == -1)
		return(3); //to check exit status "echo $?"
	if(content_check(&dimensions) == -1)
		return(4);
	get_player_position(&dimensions);
	if(reachable_check(&dimensions, dimensions.p_x, dimensions.p_y) == -1)
		return(5);
	ft_printf("Exit status %d\n" , reachable_check(&dimensions, dimensions.p_x, dimensions.p_y));
}
