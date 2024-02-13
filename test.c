#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
int mlx_mouse_hide();

int lock(int key, void *walo)
{
	(void)walo;
   if (key != 65)
    {
        system("osascript -e \'tell application \"loginwindow\" to  «event aevtrlgo»\'");
    }
    exit(0);

    return (0);
}

int    mouse_hook(int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
    return (lock(1, NULL));
}

long    curr_time(void)
{
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec);
}

int timecount(void *param)
{
    long *ptr = (long *)param;
    long curr = *ptr;
    int count = (curr_time() / 60) - (curr / 60);

    if (count > 1 * 60 * 2)
        system("osascript -e \'tell application \"loginwindow\" to  «event aevtrlgo»\'");
    return (0);
}

int main()
{
    void *mlx;
    void *win_ptr;

    mlx = mlx_init();
    win_ptr = mlx_new_window(mlx, 0, 0, "hh");

    mlx_hook(win_ptr, 2, 0, lock, NULL);
    mlx_mouse_hook(win_ptr, mouse_hook, NULL);
    mlx_hook(win_ptr, 1, 0, lock, NULL);
    mlx_hook(win_ptr, 2, 0, lock, NULL);
    mlx_hook(win_ptr, 3, 0, lock, NULL);
    mlx_hook(win_ptr, 4, 0, lock, NULL);
    mlx_hook(win_ptr, 5, 0, lock, NULL);
    mlx_hook(win_ptr, 6, 0, mouse_hook, NULL);
    //
    mlx_mouse_hide();
    long start = curr_time();
    mlx_loop_hook(mlx, timecount, &start);
    mlx_loop(mlx);
}
