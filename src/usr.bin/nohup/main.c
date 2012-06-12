#include "mowgli.h"

int main(int argc, char ** argv)
{
    int fd;
    char * buf, * home;

    buf = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s utility [arguments]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (isatty(STDOUT_FILENO))
    {
        fd = open("nohup.out", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        if (fd == -1)
        {
            home = getenv("HOME");
            if (home != NULL)
            {
                buf = mowgli_alloc(BUFSIZ);
                snprintf(buf, BUFSIZ, "%s/nohup.out", home);
                fd = open(buf, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
                if (fd == -1)
                    errx(127, "cannot open a nohup.out file");

            }
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
            err(127, NULL);
        fprintf(stderr, "appending output to %s\n", (buf ? buf : "nohup.out"));
    }

    if (isatty(STDERR_FILENO))
        dup2(fd, STDERR_FILENO);
    if (isatty(STDIN_FILENO))
    {
        fd = open("/dev/null", O_RDONLY, S_IROTH);
        if (fd != -1)
            dup2(fd, STDIN_FILENO);
    }

    mowgli_signal_install_handler(SIGHUP, SIG_IGN);

    ++argv;
    execvp(*argv, argv);

    exit(EXIT_SUCCESS);
}
