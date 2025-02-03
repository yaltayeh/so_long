#include "component.h"
#include <stdio.h>
#include <string.h>

const t_component	*get_component_by_name(const char *name);

static void opt_set_defaults(t_component_context *ctx)
{
	void				*priv;
	const t_option		*opt;
	const t_component	*component;
	void				*value_ptr;

	priv = ctx->priv;
	component = ctx->component;
	opt = component->class->options;
	while (opt->name)
	{
		value_ptr = priv + opt->offset;
		if (opt->type == OPT_TYPE_INT)
			memcpy(value_ptr, &opt->default_val, sizeof(int));
		if (opt->type == OPT_TYPE_LONG)
			memcpy(value_ptr, &opt->default_val, sizeof(long));
		if (opt->type == OPT_TYPE_PTR)
			memcpy(value_ptr, &opt->default_val, sizeof(void *));
		if (opt->type == OPT_TYPE_STRING)
			strcpy((char *)value_ptr, opt->default_val.str);
		opt++;
	}
}

t_component_context *init_component(const char *name)
{
	const t_component *component;
	t_component_context		*ctx;
	int			(*init)(t_component_context *);

	component = get_component_by_name(name);
	if (!component)
		return (NULL);
	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		goto fail;
	ctx->component = component;
	ctx->priv = calloc(1, component->size);
	if (!ctx->priv)
		goto fail;
	opt_set_defaults(ctx);
	
	init = component->init;
	if (init && init(ctx) != 0)
		goto fail;
	return (ctx);
	
fail:
	if (ctx)
	{
		if (ctx->priv)
			free(ctx->priv);
		free(ctx);
	}
	return (NULL);
}

void	render_component(t_component_context *ctx)
{
	void	(*render)(t_component_context *);

	if (!ctx)
		return ;
	render = ctx->component->render;
	if (render)
		render(ctx);
}

void	print_component_value(t_component_context *ctx)
{
	const t_component	*com;
	void				*priv;
	const t_option		*opt;
	void				*value;

	com = ctx->component;
	priv = ctx->priv;
	
	if (!com->class)
		return ;
	opt = com->class->options;
	printf("%s:\n", com->name);
	while (opt->name)
	{
		value = priv + opt->offset;
		if (opt->type == OPT_TYPE_INT)
			printf("\t%s: %d\n", opt->name, *(int *)value);
		else if (opt->type == OPT_TYPE_LONG)
			printf("\t%s: %ld\n", opt->name, *(long *)value);
		else if (opt->type == OPT_TYPE_STRING)
			printf("\t%s: %s\n", opt->name, (char *)value);
		else if (opt->type == OPT_TYPE_STRING)
			printf("\t%s: %p\n", opt->name, *(void **)value);
		opt++;
	}
}