#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct	s_all
{
	FILE	*file;
	char 	**tab;
	int		b_width;
	int		b_height;
	char	b_char;
	char	s_r;
	float	s_x;
	float	s_y;
	float	s_width;
	float	s_height;
	char	s_char;
}				t_all;

int		ft_strlen(char *str)
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

void	destroy(t_all *all)
{
	int i = 0;

	while (all->tab[i])
	{
		free(all->tab[i]);
		all->tab[i] = NULL;
		i++;
	}
	free(all->tab);
	all->tab = NULL;
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

int		back(t_all *all)
{
	int	i = 0;
	int	j;
	int	ret;

	ret = fscanf(all->file, "%d %d %c\n", &all->b_width, &all->b_height, &all->b_char);
	if (ret != 3 || all->b_width <= 0 || all->b_width > 300 || all->b_height <= 0 || all->b_height > 300)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (!(all->tab = malloc(sizeof(char *) * (all->b_height + 1))))
		return (1);
	while (i < all->b_height)
	{
		all->tab[i] = NULL;
		if (!(all->tab[i] = malloc(sizeof(char) * (all->b_width + 1))))
		{
			destroy(all);
			return(1);
		}
		j = 0;
		while (j < all->b_width)
		{
			all->tab[i][j] = all->b_char;
			j++;
		}
		all->tab[i][j] = 0;
		i++;
	}
	all->tab[i] = NULL;
	return (0);
}

int		add_shape(t_all *all)
{
	int i = 0;
	int j = 0;
	float	bx = all->s_x + all->s_width;
	float	by = all->s_y + all->s_height;
	
	while (all->tab[i])
	{
		j = 0;
		while (all->tab[i][j])
		{
			if (j >= all->s_x && j <= bx && i >= all->s_y && i <= by)
			{
				if (all->s_r == 'r')
				{
					if (j >= all->s_x + 1 && j <= bx - 1 && i >= all->s_y + 1 && i <= by - 1)
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
	return (0);
}

int		shape(t_all *all)
{
	int ret;

	all->s_r = 0;
	ret = fscanf(all->file, "%c %f %f %f %f %c\n", &all->s_r, &all->s_x, &all->s_y, &all->s_width, &all->s_height, &all->s_char);
	if (all->s_r == '\n' || all->s_r == '\0')
		return (2);
	if (ret != 6 || (all->s_r != 'r' && all->s_r != 'R') || all->s_width <= 0 || all->s_height <= 0)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	add_shape(all);
	return (0);
}

int		main(int ac, char **av)
{
	int ret = 0;
	t_all all;
	if (ac != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	if ((all.file = fopen(av[1], "r")) == NULL)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (back(&all) == 1)
	{
		fclose(all.file);
		return (1);
	}
	while (ret != 2)
	{
		ret = shape(&all);
		if (ret == 1)
		{
			fclose(all.file);
			destroy(&all);
			return (1);
		}
	}
	fclose(all.file);
	print_tab(&all);
	destroy(&all);
	return (0);
}
