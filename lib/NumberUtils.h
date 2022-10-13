#ifndef OS_2_PROJET_GROUPE_3_INTUTIL_H
#define OS_2_PROJET_GROUPE_3_INTUTIL_H

int lenInt(int i);
int lenDouble(double d, int maxDecimal);

/*
 * Renvoit le nombre de chiffres dans le nombre i
 */
int lenInt(int i) {
    int copy = i;
    int digit = 0;
    do {
        copy /= 10;
        digit++;
    } while (copy != 0);
    return digit;
}

/*
 * Renvoit le nombre de chiffres dans le nombre i additionner à "maxDecimal"
 */
int lenDouble(double d, int maxDecimal) {
    int digitInt = 0;
    return lenInt((int) d) + maxDecimal;
}
#endif //OS_2_PROJET_GROUPE_3_INTUTIL_H
