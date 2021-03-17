

void			print_map(t_board f, int **map)
{
	int x;
	int y;

	fd = open("heatmap.txt", O_WRONLY); //test
	x = 0;
	y = 0;
	while (x < f.w)
	{
		ft_dprintf(fd, "%6d ", x);
		x++;
	}
	x = 0;
	ft_dprintf(fd, "\n \n");
	while (y < f.h)
	{
		while(x < f.w)
		{
			ft_dprintf(fd, "%6d ", map[y][x]);
			x++;
		}
		ft_dprintf(fd, "\n");
		x = 0;
		y++;
	}
