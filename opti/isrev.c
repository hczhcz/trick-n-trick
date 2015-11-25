#include <stdio.h>

int isRev_1(int i) {
    int rev = 0;
    int tmp = i;

    while (tmp) {
        rev *= 10;
        rev += tmp % 10;
        tmp /= 10;
    }

    return rev == i;
}

int isRev_2(int i) {
    #define REV_TBL_SIZE 5
    static int tbl[][REV_TBL_SIZE] = {
        {1000000001, 100000010, 10000100, 1001000, 110000},
        { 100000001,  10000010,  1000100,  101000,  10000},
        {  10000001,   1000010,   100100,   11000,      0},
        {   1000001,    100010,    10100,    1000,      0},
        {    100001,     10010,     1100,       0,      0},
        {     10001,      1010,      100,       0,      0},
        {      1001,       110,        0,       0,      0},
        {       101,        10,        0,       0,      0},
        {        11,         0,        0,       0,      0},
        {         1,         0,        0,       0,      0},
        {         0,         0,        0,       0,      0},
    };

    if (i < 0) {
        i = -i;
    }

    int *tbl_p = (int *) tbl;
    while (i < *tbl_p) {
        tbl_p += REV_TBL_SIZE;
    }

    int tbi, mask;
    for (
        tbi = 0;
        tbi < REV_TBL_SIZE && (mask = tbl_p[tbi]);
        ++tbi
    ) {
        if (mask != 1000000001 && i >= 5 * mask) {
            i -= 5 * mask;
        }
        if (i >= 2 * mask) {
            i -= 2 * mask;
        }
        if (i >= mask) {
            i -= mask;
        }
        if (i >= mask) {
            i -= mask;
        }
        if (i & ((1 << tbi) - 1)) {
            return 0;
        }
    }

    return !i;
}

int main(void) {
    int i;
    int count = 0;

    for (i = 2000000000; i < 2147483647; ++i) {
    // for (i = 0; i < 123454321; ++i) {
    // for (i = 123454321; i < 200000000; ++i) {
        if (isRev_2(i)) {
            ++count;
        }
        // if (isRev_1(i) != isRev_2(i)) {
        //     printf("%d\n", i);
        // }
    }

    printf("%d\n", count);

    return 0;
}
