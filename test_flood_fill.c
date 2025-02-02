#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NB_COLS 10
#define NB_ROWS 9

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
		if (r < 0 || r >= NB_ROWS || c < 0 || c >= NB_COLS)
			continue;
		if (map[r * NB_COLS + c] != '0')
			continue;
		i++;
		map[r * NB_COLS + c] = '2' + i / 10;
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
	char	*map = "0000000001"
				   "0111111101"
				   "0100000101"
				   "0101110101"
				   "0101010101"
				   "0101000101"
				   "0101111101"
				   "0100000001"
				   "0111111111";
	
	map = strdup(map);
	test_flood_fill(map, 4, 4);
	for (int r = 0; r < NB_ROWS; r++)
	{
		for (int c = 0; c < NB_COLS; c++)
			printf("%c", map[r * NB_COLS + c]);
		printf("\n");
	}
}