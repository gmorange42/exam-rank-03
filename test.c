#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_back
{
	float	width;
	float	height;
	char	c;
}				t_back;

typedef struct	s_figure
{
	char	r;
	float	x;
	float	y;
	float	width;
	float	height;
	char	c;
}				t_figure;

typedef struct	s_all
{
	FILE *file;
	char **tab;
	t_back back;
	t_figure figure;
}				t_all;

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
void	print_tab(t_all *all)
{
	int i;

	i = 0;
	while (all->tab[i])
	{
		ft_putstr(all->tab[i]);
		ft_putstr("\n");
		i++;
	}
}

void	free_tab(t_all *all)
{
	int i;

	i = 0;
	if (all->tab != NULL)
	{
	while (all->tab[i])
	{
		free(all->tab[i]);
		all->tab[i] = NULL;
		i++;
	}
	free(all->tab);
	}
	all->tab = NULL;
}

int		stock_back(t_all *all)
{
	int i;
	int j;

	i = 0;
	if (!(all->tab = malloc(sizeof(char *) * ((int)all->back.height + 1))))
	{
		ft_putstr("malloc tab failed\n");
		return (1);
	}
	all->tab[(int)all->back.height] = 0;
	while (i < (int)all->back.height)
	{
		if (!(all->tab[i] = malloc(sizeof(char) * ((int)all->back.width + 1))))
		{
			ft_putstr("malloc tab[i] failed\n");
			return (1);
		}
		j = 0;
		while (j < (int)all->back.width)
		{
			all->tab[i][j] = all->back.c;
			j++;
		}
		all->tab[i][j] = '\0';
		i++;
	}
	return (0);
}

int		check_and_stock_back(t_all *all)
{
	int ret;
	char test;
	ret = fscanf(all->file, "%f %f %c", &all->back.width, &all->back.height, &all->back.c);
	if (ret != 3)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return(1);
	}
	fscanf(all->file, "%c", &test);
	if (test != '\n' && test != '\0')
	{
		ft_putstr("Error: Operation file corrupted\n");
		return(1);
	}
	if ((int)all->back.width < 0 || (int)all->back.height > 300 || (int)all->back.height < 0 || (int)all->back.height > 300)
		return (1);
	return(stock_back(all));
}

void	intizer(t_all* all, int *x, int *y, int *w, int *h)
{
	if (all->figure.x != (int)all->figure.x)
	{
		if ((int)all->figure.x >= 0)
			*x = (int)all->figure.x + 1;
		else
			*x = (int)all->figure.x - 1;
	}
	else
		*x = (int)all->figure.x;
	if (all->figure.y != (int)all->figure.y)
	{
		if ((int)all->figure.y >= 0)
			*y = (int)all->figure.y + 1;
		else
			*y = (int)all->figure.y - 1;
	}
	else
		*y = (int)all->figure.y;
	*w = all->figure.x + all->figure.width;
	*h = all->figure.y + all->figure.height;
}
/*
void	add_figure(t_all *all)
{
	int x;
	int y;
	int w;
	int	h;
	int i;
	int j;

	intizer(all, &x, &y, &w, &h);
	i = y;
	j = x;
	printf("x %d\ny %d\nw %d\nh %d\ni %d\nj %d\n", x, y, w, h, i, j);
	while (i <= h)
	{
		j = x;
		while(j <= w)
		{
			if (i < all->back.height && j < all->back.width && i >= 0 && j >= 0)
			{
				if (all->figure.r == 'r')
				{
					if (i == y || i == h || j == x || j == w)
						all->tab[i][j] = all->figure.c;
				}
				else
					all->tab[i][j] = all->figure.c;
			}
			j++;
		}
		i++;
	}
}
*/

void	add_figure(t_all *all)
{
	int i = 0;
	int j = 0;
	float	bx = all->figure.x + all->figure.width;
	float	by = all->figure.y + all->figure.height;

	while (i < all->back.height)
	{
		j = 0;
		while (j < all->back.width)
		{
			if (i >= all->figure.y && i <= bx && j >= all->figure.x && j <= by)
				all->tab[i][j] = all->figure.c;
			j++;
		}
		i++;
	}
}

int		figure(t_all *all)
{
	int ret;
	char	test;
	all->figure.r = 0;
	ret = fscanf(all->file, "%c %f %f %f %f %c", &all->figure.r, &all->figure.x, &all->figure.y, &all->figure.width, &all->figure.height, &all->figure.c);
	if (all->figure.r == '\0' || all->figure.r == ' ' || all->figure.r == '\n')
		return (2);
	if (ret != 6)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return(1);
	}
	fscanf(all->file, "%c", &test);
	if (test != '\n' && test != '\0')
	{
		ft_putstr("Error: Operation file corrupted\n");
		return(1);
	}
	if (test == '\0')
		return(2);
	add_figure(all);
	return (0);
}

int 	main(int ac, char **av)
{
	t_all all;
	all.tab = NULL;

	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return(1);
	}
	all.file = fopen(av[1], "r");
	if (all.file == NULL)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return(1);
	}
	if (check_and_stock_back(&all) != 0)
	{
		ft_putstr("lol\n");
		free_tab(&all);
		fclose(all.file);
		return (1);
	}
	while (figure(&all) != 2)
		;
	print_tab(&all);
	free_tab(&all);
	fclose(all.file);
	return (0);
}
