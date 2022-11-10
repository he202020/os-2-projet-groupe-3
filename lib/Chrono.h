#include <time.h>
#include <unistd.h>
#include <stdio.h>

void chrono(int delay) {
    // time_t start = time(NULL);

    for (int i = 0; i < delay; ++i) {
        time_t end = time(NULL);
        setCourseState(false);
        // int diff = difftime(end, start);
        // printf("%d\n", diff);
        sleep(1);
    }
}