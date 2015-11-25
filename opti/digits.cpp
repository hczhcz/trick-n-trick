#include <iostream>
#include <cmath>
using namespace std;

int digits[4];

#define GET(i, amount, damount) \
    y = (amount - x) >> 31; \
    x += y * amount; \
    digits[i] -= y * damount;

void f(float value) {
    int x = floor(value) + 1;
    int y;

    GET(0, 4000, 4);
    GET(0, 2000, 2);
    GET(0, 2000, 2);
    GET(0, 1000, 1);
    GET(1, 400, 4);
    GET(1, 200, 2);
    GET(1, 200, 2);
    GET(1, 100, 1);
    GET(2, 40, 4);
    GET(2, 20, 2);
    GET(2, 20, 2);
    GET(2, 10, 1);
    GET(3, 4, 4);
    GET(3, 2, 2);
    GET(3, 2, 2);
    GET(3, 1, 1);
}

int main() {
    while (true) {
        digits[0] = 0;
        digits[1] = 0;
        digits[2] = 0;
        digits[3] = 0;

        float value;
        cin >> value;

        f(value);

        cout << digits[0] << ' ' <<
                digits[1] << ' ' <<
                digits[2] << ' ' <<
                digits[3] << endl;
    }
}
