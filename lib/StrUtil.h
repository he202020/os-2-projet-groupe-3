#ifndef OS_2_PROJET_GROUPE_3_STRUTIL_H
#define OS_2_PROJET_GROUPE_3_STRUTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "NumberUtils.h"

void timeToStr(char buffer[], double time);
int sizeForTimeToStr(double time);

/*
 * Convertit un temps "time" en un format str "xh ym zs"
 * et le stock dans "buffer"
 */
void timeToStr(char buffer[], double time) {
    int hour = (int) time / 3600;
    int minute = ((int) time % 3600) / 60;
    double second = ((int) time % 3600) % 60;
    second += time - (int) time;

    int maxlen = sizeForTimeToStr(time);
    snprintf(buffer, maxlen, "%dm %2.3fs", minute, second);

}

/*
 * Renvoit la taille que le buffer doit avoir pour utiliser la méthode
 * timeToStr()
 */
int sizeForTimeToStr(double time) {
    int hour = (int) time / 3600;
    int minute = ((int) time % 3600) / 60;
    double second = ((int) time % 3600) % 60;
    second += time - (int) time;
    return strlen("%dH %dm %ds") + lenInt(hour) + lenInt(minute) + lenDouble(second, 3);
}
#endif //OS_2_PROJET_GROUPE_3_STRUTIL_H