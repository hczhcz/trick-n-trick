#include <iostream>

using namespace std;

typedef unsigned long long ii;
const ii maxsize = 16;
typedef ii data_t[maxsize];

static bool solve(
    const ii xsize, const ii ysize, data_t &map, const ii y = 0,
    const ii used_col = 0, const ii used_p = 0, const ii used_n = 0
) {
    // if finished
    if (y >= ysize) {
        return true;
    }

    // try placing
    for (ii x = 0; x < xsize; ++x) {
        // update bitwise masks
        ii new_col   = used_col   | (1 << x);
        ii new_p     = used_p     | (1 << (x + y));
        ii new_n     = used_n     | (1 << (x - y + ysize));

        // check conflicts
        if (new_col == used_col || new_p == used_p || new_n == used_n) {
            continue;
        }

        // solve
        if (
            solve(xsize, ysize, map, y + 1, new_col, new_p, new_n)
        ) {
            map[y] = 1 << x;
            return true;
        } else {
            continue;
        }
    }

    return false;
}

int main() {
    for (ii ysize = 1; ysize <= maxsize; ++ysize) {
        data_t map;

        ii xsize = ysize;

        // solve
        while (!solve(xsize, ysize, map)) {
            ++xsize;
        }

        cout << "=== " << ysize << " ===" << endl;

        // output
        for (ii y = 0; y < ysize; ++y) {
            for (ii x = 0; x < xsize; ++x) {
                cout << ((map[y] >> x) & 1);
            }
            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
