#include "mowgli.h"

#define fail \
    printf("usage %s seconds\n", argv[0]); \
    exit(EXIT_FAILURE);

void signal_alarm(int signum)
{
    exit(EXIT_FAILURE);
}

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fail;
    }

    if (!isdigit(argv[1][0]))
    {
        fail;
    }

    mowgli_signal_install_handler(SIGALRM, signal_alarm);
    sleep(strtol(argv[1], (char **)NULL, 10));

    exit(0);
}
