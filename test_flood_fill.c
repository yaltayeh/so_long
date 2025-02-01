#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_cell
{
	int r;
	int c;
	struct s_cell *next;
}	t_cell;

int	add_new_cell(t_cell **lst, t_cell **tail, int r, int c)
{
	t_cell	*new;

	new = malloc(sizeof(t_cell));
	if (!new)
		return (-1);
	new->r = r;
	new->c = c;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
	return (0);
}

int	pop_cell(t_cell **lst, t_cell **tail, int *r, int *c)
{
	t_cell	*cell;

	cell = *lst;
	if (!cell)
		return (0);
	*r = cell->r;
	*c = cell->c;
	*lst = cell->next;
	if (!*lst)
		*tail = NULL;
	free(cell);
	return (1);
}

int	test_flood_fill(char *map, int r, int c)
{
	static int i = 0;
	t_cell	*lst = NULL;
	t_cell	*tail = NULL;

	add_new_cell(&lst, &tail, r, c);
	while (pop_cell(&lst, &tail, &r, &c))
	{
		if (r < 0 || r >= 9 || c < 0 || c >= 9)
			continue;
		if (map[r * 9 + c] != '0')
			continue;
		i++;
		map[r * 9 + c] = '1' + i / 10;
		if (!add_new_cell(&lst, &tail, r - 1, c)
			|| !add_new_cell(&lst, &tail, r + 1, c)
			|| !add_new_cell(&lst, &tail, r, c - 1)
			|| !add_new_cell(&lst, &tail, r, c + 1)
			|| !add_new_cell(&lst, &tail, r - 1, c - 1)
			|| !add_new_cell(&lst, &tail, r - 1, c + 1)
			|| !add_new_cell(&lst, &tail, r + 1, c - 1)
			|| !add_new_cell(&lst, &tail, r + 1, c + 1))
		{
			// destroy lst
			return (-1);
		}
	}
	return (0);
}

int main()
{
	char	*map = "000000000"
				   "000000000"
				   "000000000"
				   "000000000"
				   "000000000"
				   "000000000"
				   "000000000"
				   "000000000"
				   "000000000";
	
	map = strdup(map);
	for (int r = 0; r < 9; r++)
		printf("%.9s\n", map + r * 9);
	test_flood_fill(map, 4, 4);
	printf("\n\n");
	for (int r = 0; r < 9; r++)
		printf("%.9s\n", map + r * 9);

	
}