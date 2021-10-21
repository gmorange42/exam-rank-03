#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_data
{
	int	bwidth;
	int	bheight;
	int	back;
	int	r;
	int x;
	int y;
	int fwidth;
	int	fheight;
	int	fchar;
}				t_data;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#include <stdio.h>

int main(int ac, char **av)
{
	char temp[10];
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
	if (fread(temp, sizeof(char), 1, file) == 0)
	{
	   write(1, "lol\n", 4);
	   exit (1);
	}
}
