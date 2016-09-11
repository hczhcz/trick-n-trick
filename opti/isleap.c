#include <stdio.h>

int isLeap_1(int year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int isLeap_2(int year) {
    if (year < 0) year = -year;
    int v = (year * 0xa3d70b) >> 23;
    return (year & 3) == 0 && (v & -v & 0x180) == 0;
}

int main(void) {
    int i;

    for (i = -1000000; i < 1000000; ++i) {
        if (isLeap_1(i) != isLeap_2(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}
