#include "../lib/libft/libft.h"

int	main(void)
{
	int		fd;
	char	*line;
	fd = open("map", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error reading!̣\n");
		return (1);
	}
	else
	{
		while ((line = get_next_line(fd)) != NULL)
		{
			ft_printf("%s", line);
			free(line);
		}
		free(line);
	}
	close(fd);
	return (0);
}
