// https://zhuanlan.zhihu.com/p/35845018

#include <sstream>
#include <iostream>

using namespace std;

// 2 + 2
// A 1 2 a
// A 1 b
// B 2 a
// B 2 1 b

// 3 + 3
// A 1 3 a
// A 1 4 b
// A 1 c
// B 2 3 a
// B 2 4 b
// B 2 c
// C 3 a
// C 4 b
// C 4 1 c

// 4 + 4
// A 1 4 a
// A 1 5 b
// A 1 6 c
// A 1 d
// B 2 4 a
// B 2 5 b
// B 2 6 c
// B 2 d
// C 3 4 a
// C 3 5 b
// C 3 6 c
// C 3 d
// D 4 a
// D 5 b
// D 6 c
// D 6 1 d

// 2n + 2n
// A 1 2 a
// A 1 3 b
// B 2 1 a
// B 2 3 b

// n + 2n
// A 1 2 a
// A 2 1 b

// 3n + 4n
// A 1 2 a
// A 1 4 b
// C 5 2 a
// C 5 4 b
// B 3 2 a
// B 3 4 b
// B 3 1 c
// B 3 5 d
// A 2 1 c
// A 2 5 d
// C 4 1 c
// C 4 5 d

long data[100];

int main() {
    string s;
    while (getline(cin, s)) {
        if (!s.size()) continue;

        int last = 0;

        istringstream is {s};

        while (true) {
            is >> ws;
            char c = is.peek();

            if (c >= 'A' && c <= 'Z') {
                is >> c;

                data[1] = 1l << (c - 64);
                last = 1;
            } else if ((c >= '0' && c <= '9') || c == '-') {
                int next;
                is >> next;

                if (next > 0) {
                    next = next * 2;
                } else if (next < 0) {
                    next = -next * 2 + 1;
                }

                data[last] = data[next] = data[last] | data[next];

                last = next ^ 1;
            } else if (c >= 'a' && c <= 'z') {
                is >> c;

                data[0] = 1l << (c - 64);

                data[last] = data[0] = data[last] | data[0];

                break;
            } else {
                is >> c;
            }
        }

        while (s.size() < 16) {
            s += ' ';
        }

        cout << s << "//";

        for (int i = 0; i < 10; ++i) {
            char ll = '.';
            char rr = '.';

            for (int j = 0; j < 64; ++j) {
                if (data[i * 2] & (1l << j)) {
                    if (ll == '.') {
                        ll = j + 64;
                    } else {
                        ll = 'x';
                    }
                }
                if (data[i * 2 + 1] & (1l << j)) {
                    if (rr == '.') {
                        rr = j + 64;
                    } else {
                        rr = 'x';
                    }
                }
            }

            if (i) {
                cout << ' ' << ll << rr;
            } else {
                cout << ' ' << rr << "->" << ll;
            }
        }
        cout << endl;
    }
}
