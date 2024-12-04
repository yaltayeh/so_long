#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
} t_mlx_data;

int end_program(void *mlx_ptr, void *win_ptr)
{
    mlx_destroy_window(mlx_ptr, win_ptr);
    exit(0);
}

int mouse_hook(int button,int x,int y,void *param)
{
    printf()
}

int key_hook(int keycode, void *param)
{
    t_mlx_data *data;

    data = (t_mlx_data *)param;
    printf("key: %d\n", keycode);
    if (keycode == 65307) // ESC
        end_program(data->mlx_ptr, data->win_ptr);
    return (0);
}

int main()
{
    t_mlx_data data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
    {
        perror("mlx");
        return (1);
    }
    data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "Test");
    if (!data.win_ptr)
    {
        perror("window");
        return (1);
    }
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_mouse_hook(data.win_ptr, )
    mlx_loop(data.mlx_ptr);
    return (0);
}