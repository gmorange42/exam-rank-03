#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_all
{
	FILE	*file;
	char	**back;
	float	b_width;
	float	b_height;
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

int		ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	return(1);
}

void	destroy(t_all *all)
{
	int i = 0;

	while (all->back[i])
	{
		free(all->back[i]);
		all->back[i] = NULL;
		i++;
	}
	free(all->back);
	all->back = NULL;
}

void	print_tab(t_all *all)
{
	int i = 0;

	while (all->back[i])
	{
		ft_putstr(all->back[i]);
		ft_putstr("\n");
		i++;
	}
}

int		malloc_and_stock_back(t_all *all)
{
	int i = 0;
	int j;
	all->back = malloc(sizeof(char *) * ((int)all->b_height + 1));
	if (all->back == NULL)
		return(1);
	all->back[(int)all->b_height] = NULL;
	while (i < (int)all->b_height)
	{
		j = 0;
		all->back[i] = malloc(sizeof(char) * (all->b_width + 1));
		if (all->back[i] == NULL)
			return (1);
		while (j < (int)all->b_width)
		{
			all->back[i][j] = all->b_char;
			j++;
		}
		all->back[i][j] = '\0';
		i++;
	}
	return (0);
}

int		back(t_all *all)
{
	char test;
	if ((fscanf(all->file, "%f %f %c", &all->b_width, &all->b_height, &all->b_char)) != 3)
		return(ft_putstr("Error: Operation file corrupted\n"));
	fscanf(all->file, "%c", &test);
	if (test != '\n' && test != '\0')
		return(ft_putstr("Error: Operation file corrupted\n"));
	if ((int)all->b_width <= 0 || (int)all->b_width > 300 || (int)all->b_height <= 0 || (int)all->b_height > 300)
		return(ft_putstr("Error: Operation file corrupted\n"));
	malloc_and_stock_back(all);
	return (0);
}
/*
void	add_shape(t_all *all)
{
	int i = 0;
	int j = 0;

	int bx = all->s_width + all->s_x;
	int yx = all->s_height + all->syx;

	while (all->back[i])
	{
		while (all->back[i][j])
		{
			if (i >= all->
			j++;
		}
		i++;
	}
}
*/
int		shape(t_all *all)
{
	char	test;
	all->s_r = '\0';
	if (((fscanf(all->file, "%c %f %f %f %f %c", &all->s_r,  &all->s_x, &all->s_y, &all->s_width, &all->s_height, &all->s_char)) != 6) && all->s_r != '\0')
		return(ft_putstr("Error: Operation file corrupted\n"));
	printf("%c %f %f %f %f %c\n", all->s_r,  all->s_x, all->s_y, all->s_width, all->s_height, all->s_char);
	if (all->s_r == '\0')
		return (2);
	if (all->s_r != 'r' && all->s_r != 'R')
		return(ft_putstr("Error: Operation file corrupted\n"));
	fscanf(all->file, "%c", &test);
	if (test != '\n' && test != '\0')
		return(ft_putstr("Error: Operation file corrupted\n"));
//	add_shape(all);
	return (0);
}

int main(int ac, char **av)
{
	int ret = 5;
	t_all all;
	if (ac != 2)
		return (ft_putstr("Error: argument\n"));
	if ((all.file = fopen(av[1], "r")) == NULL)
		return(ft_putstr("Error: Operation file corrupted\n"));
	if (back(&all) == 1)
		return (1);
	print_tab(&all);
	while (ret != 2)
	{
		ret = shape(&all);
		if (ret == 1)
		{
			destroy(&all);
			return(1);
		}
	}
	destroy(&all);
	return (0);
}
