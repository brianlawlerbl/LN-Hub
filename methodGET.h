#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>

int method_GET(int response_code, int client, char *resource, char *out, int outlen, int BLOCK);
