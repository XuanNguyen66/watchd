#include "parseline.h"

void write_logging(SecWatchManager *manage){
    printf("tôi đã được gọi\n");
    time_t now = time(NULL);
    struct tm *ts;
    char buf[80];

    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);

    fprintf(stderr, "Service: [%s]\nTime failed: [%s]", manage->services->name, buf);

    puts(buf);

}