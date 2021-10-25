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
	ft_putstr("LOL\n");
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

void	intizer(t_all* all)
{
	if (all->figure.x != (int)all->figure.x)
		all->figure.x = (int)all->figure.x + 1;
	if (all->figure.y != (int)all->figure.y)
		all->figure.y = (int)all->figure.y + 1;
	if (all->figure.width != (int)all->figure.width)
		all->figure.width = (int)all->figure.width + 1;
	if (all->figure.height != (int)all->figure.height)
		all->figure.height = (int)all->figure.height + 1;
	if (all->figure.x + all->figure.width < (int)all->figure.x + (int)all->figure.width)
	{
		puts("1");
		all->figure.x += 1;
	}
	if (all->figure.y + all->figure.height < (int)all->figure.y + (int)all->figure.height)
	{
		puts("2");
		all->figure.y += 1;
	}
	printf("TEST %f \n", all->figure.x);
}

void	add_figure(t_all *all)
{
	int i;
	int j;

	intizer(all);
	i = (int)all->figure.y;
	j = (int)all->figure.x;
	while (i <= ((int)all->figure.height + (int)all->figure.y))
	{
		printf("i = %f %d\n", all->figure.y, (int)all->figure.height + (int)all->figure.y);
		j = (int)all->figure.x;
		printf("j = %f %d\n", all->figure.x, (int)all->figure.width + (int)all->figure.x);
		while(j <= ((int)all->figure.width + (int)all->figure.x))
		{
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
	printf("ret = %d\n%c %f %f %f %f %c\n",ret , all->figure.r, all->figure.x, all->figure.y, all->figure.width, all->figure.height, all->figure.c);
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
