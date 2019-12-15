#include <iostream>

using namespace std;

int main() {
    long sum = 0;
    long scale = 10;

    for (long i = 0; i < 1000000000; ++i) {
        long x = i;

        // banker's #1

        // auto quotient = x / (scale / 2);

        // if (quotient * (scale / 2) == x) {
        //     x = ((quotient + 1) / 4 + (quotient + 2) / 4) * scale;
        // } else {
        //     x = (quotient + 1) / 2 * scale;
        // }

        // banker's #2

        auto quotient = (x + scale / 2) / scale;

        if (quotient * scale == x + scale / 2) {
            x = (quotient & ~1) * scale;
        } else {
            x = quotient * scale;
        }

        // banker's #3

        // x = (x + scale / 2 - (~(x / scale) & 1)) / scale * scale;

        // rounding up

        // x = (x + scale / 2) / scale * scale;

        sum += x;
        sum += 7654321;
        sum *= 1234567;
    }

    cout << sum << endl;
}
