#include <iostream>
#include <functional>

#define lambda(NAME, CAP, PROTO, BODY) \
    [&]() { \
        std::function<auto PROTO> (NAME) = CAP PROTO {BODY}; \
        return (NAME); \
    }()

int main() {
    auto fac = lambda(fac, [&], (int x) -> int, {
        if (x < 1) {
            return 1;
        } else {
            return x * fac(x - 1);
        }
    });

    std::cout << fac(3) << std::endl;
    return 0;
}
