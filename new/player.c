#include "component.h"
#include "object.h"
#include <stdio.h>

typedef struct s_player
{
	t_object	obj;
}	t_player;

#define OFFSET(x) offsetof(t_player, x)

static const t_option	player_options[] = {
	OBJECT_OPTIONS(obj),
	{ 0 }
};

COMPONENT_DEFINE_CLASS(player)

const t_component player = {
	.name	= "player",
	.class	= &player_class,
	.size 	= sizeof(t_player),
};