#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int get_elapsed_time(struct timeval	*start_time)
{
    struct timeval  now;
    int             seconds;
    int             useconds;

    gettimeofday(&now, NULL);
    seconds = (&now)->tv_sec - start_time->tv_sec;
    useconds = (&now)->tv_usec - start_time->tv_usec;
    return (seconds * 1000 + useconds / 1000);
}

int main()
{
    struct timeval	start_time;
    int time;

    gettimeofday(&start_time, NULL);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    usleep(10000);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    usleep(20000);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    usleep(1000);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    usleep(2000);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    usleep(10000);
    time = get_elapsed_time(&start_time);
    printf("%d\n", time);
    return (0);
}