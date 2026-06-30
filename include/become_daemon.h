#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H


#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#define BD_NO_CHDIR 01
#define BD_NO_CLOSE_FILES 02
#define BD_NO_REOPEN_STD_FDS 04
#define BD_NO_UMASKO 010
#define BD_MAX_CLOSE 8192

int become_daemon(int flags);

#endif
