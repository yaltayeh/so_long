#include "component.h"
#include "string.h"

const t_component player;

const t_component *components[] = {
	&player,
	NULL
};

const t_component	*get_component_by_name(const char *name)
{
	const t_component **current;

	current = (const t_component **)components;
	while (*current)
	{
		if (strcmp((*current)->name, name) == 0)
			return (*current);
		current++;
	}
	return (NULL);
}
