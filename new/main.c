#include <stdio.h>
#include "component.h"

int main()
{
	t_component_context *ctx;

	ctx = init_component("player");
	if (!ctx)
		return (1);
	print_component_value(ctx);
	return (0);
}