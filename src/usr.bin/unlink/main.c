#include "mowgli.h"

int main(int argc, char ** argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (unlink(argv[1]) == -1)
    {
        fprintf(stderr, "%s: %s: %s\n", argv[0], argv[1], strerror(errno));
        exit(errno);
    }

    exit(EXIT_SUCCESS);
}
