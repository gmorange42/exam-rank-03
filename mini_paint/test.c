#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_all
{
	FILE	*file;
	char	**tab;
	int	b_width;
	int	b_height;
	char	b_char;
	char	s_c;
	float	s_x;
	float	s_y;
	float	s_r;
	char	s_char;
}		t_all;

int	ft_strlen(char *str)
{
	int i = 0;

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
	int i = 0;
	while (all->tab[i])
	{
		ft_putstr(all->tab[i]);
		ft_putstr("\n");
		i++;
	}
}

int	back(t_all *all)
{
	char	test;
	int i = 0;
	int j;
	if ((fscanf(all->file, "%d %d %c", &all->b_width, &all->b_height, &all->b_char)) != 3)
			{
				ft_putstr("Error: Operation file corrupted\n");
				return (1);
			}	
	fscanf(all->file, "%c", &test);
	if (test != '\n')
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}	
	if (all->b_width <= 0 || all->b_width > 300 || all->b_height <= 0 || all->b_height > 300)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}	

	if (!(all->tab = malloc(sizeof(char *) * (all->b_height + 1))))
		return(1);
	all->tab[all->b_height] = NULL;
	while (i < all->b_height)
	{
		j = 0;
		all->tab[i] = malloc(sizeof(char) * (all->b_width + 1));
		while (j < all->b_width)
		{
			all->tab[i][j] = all->b_char;
			j++;
		}
		all->tab[i][j] = '\0';
		i++;
	}
	return (0);
}

void	add_shape(t_all *all)
{
	float	pos;
	int i = 0;
	int j;
	while (all->tab[i])
	{
		j = 0;
		while (all->tab[i][j])
		{
			pos = sqrtf(((j - all->s_x) * (j - all->s_x)) + ((i - all->s_y) * (i - all->s_y)));
			if (pos <= all->s_r)
			{
				if (all->s_c == 'c')
				{
					if (pos <= all->s_r - 1)
						;
					else
						all->tab[i][j] = all->s_char;
				}
				else
					all->tab[i][j] = all->s_char;
			}
			j++;
		}
		i++;
	}
}

int	shape(t_all *all)
{
	int ret;
	char	test;
	all->s_c = 0;
	ret = fscanf(all->file, "%c %f %f %f %c", &all->s_c, &all->s_x, &all->s_y, &all->s_r, &all->s_char);
	if (all->s_c == '\0')
		return (2);
	fscanf(all->file, "%c", &test);
	if (test == '\0')
		return (2);
	if (ret != 5 || (test != '\n' && test != '\0'))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	add_shape(all);
	return (0);
}

int	main(int ac, char **av)
{
	int ret = 0;
	t_all all;
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	if(!(all.file = fopen(av[1], "r")))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (back(&all) == 1)
		return (1);
	while (ret != 2)
	{
		if ((ret = shape(&all)) == 1)
			return (1);
	}
	print_tab(&all);
	return (0);
}
