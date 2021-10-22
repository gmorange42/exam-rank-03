#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_data
{
	char	**tab;
	char	temp;
	float	bwidth;
	float	bheight;
	char	bchar;
	char	r;
	float	x;
	float 	y;
	float 	fwidth;
	float	fheight;
	char	fchar;
}				t_data;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_tab(t_data *all)
{
	int i = 0;
	int j = 0;

	while (all->tab[i])
	{
		j = 0;
		while (all->tab[i][j])
		{
			write(1, &all->tab[i][j], 1);
			j++;
		}
		i++;
	}
}

void	set_tab(t_data *all)
{
	int i = 0;
	int j;
	all->tab = malloc(sizeof(char *) * ((int)all->bheight));
	all->tab[(int)all->bheight] = 0;
	while (i < (int)all->bheight)
	{
		all->tab[i] = malloc(sizeof(char) * (int)all->bwidth + 1);
		i++;
	}
	i = 0;
	while (i < (int)all->bheight)
	{
		j = 0;
		while (j < (int)all->bwidth)
		{
			all->tab[i][j] = all->bchar;
			all->tab[i][j + 1] = '\n';
			all->tab[i][j + 2] = '\0';
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_data	all;
	FILE *file;
	if (ac != 2)
	{
		write(1, "Error: argument\n", ft_strlen("Error: argument\n"));
		exit(1);
	}
	if ((file = fopen(av[1], "r")) == NULL)
	{
		write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		exit(1);
	}
	int ret;

		ret = fscanf(file, "%f %f %c", &all.bwidth, &all.bheight, &all.bchar);
		printf("A %f %f %c\n", all.bwidth, all.bheight, all.bchar);
		ret = fscanf(file, "%[^\n]", &all.temp);
		if (all.temp != 0)
		{
			write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
			return(0);
		}
		set_tab(&all);
		ret = fscanf(file, "%c", &all.temp);
		all.temp = 0;

		ret = fscanf(file, "%c %f %f %f %f %c", &all.r, &all.x, &all.y, &all.fwidth, &all.fheight, &all.fchar);
		print_tab(&all);
		printf("B %c %f %f %f %f %c\n", all.r, all.x, all.y, all.fwidth, all.fheight, all.fchar);
//	{
//		printf("%d TEST %s\n", ret, temp);
//	}
	/*
	if (fread(temp, sizeof(char), 1, file) == 0)
	{
	   write(1, "lol\n", 4);
	   exit (1);
	}*/
}
