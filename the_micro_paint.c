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

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	destroy_tab(t_data *all)
{
	int i;

	i = 0;
	while (all->tab[i])
	{
		free(all->tab[i]);
		all->tab[i] = NULL;
		i++;
	}
	free(all->tab);
	all->tab = NULL;
}

void	set_tab(t_data *all)
{
	int i;
	int j;

	i = 0;
	all->tab = malloc(sizeof(char *) * ((int)all->bheight + 1));
	all->tab[(int)all->bheight] = 0;
	while (i < (int)all->bheight)
	{
		j = 0;
		all->tab[i] = malloc(sizeof(char) * ((int)all->bwidth + 1));
		while(j < (int)all->bwidth)
		{
			all->tab[i][j] = all->bchar;
			j++;
		}
		all->tab[i][j] = 0;
		i++;
	}
}

void	print_tab(t_data *all)
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
	all.temp = 0;
	ret = fscanf(file, "%[^\n]", &all.temp);
	if (all.temp != 0)
	{
		write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return(0);
	}
	ret = fscanf(file, "%c", &all.temp);
	all.temp = 0;
	set_tab(&all);
	print_tab(&all);
	while (ret > 0)
	{
		ret = fscanf(file, "%c %f %f %f %f %c", &all.r, &all.x, &all.y, &all.fwidth, &all.fheight, &all.fchar);
		printf("B %c %f %f %f %f %c\n", all.r, all.x, all.y, all.fwidth, all.fheight, all.fchar);
		fscanf(file, "%[^\n]", &all.temp);
		if (all.temp != 0)
		{
			write(1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
			return(0);
		}
		fscanf(file, "%c", &all.temp);
		all.temp = 0;
	}
	destroy_tab(&all);
	fclose(file);
}
