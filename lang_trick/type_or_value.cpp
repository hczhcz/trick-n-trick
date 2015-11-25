#include <iostream>
#include <string>
#include <typeinfo>

class Magic {
public:
    template <class T>
    Magic(const T &value) {
        std::cout << "Value: " << value << std::endl;
    }
};

template <class T>
void printType(Magic (*value)(T)) {
    std::cout << "Type: " << typeid(T).name() << std::endl;
}

void printType(Magic *) {}

#define F(x) ( \
    [&]() { \
        Magic magic(x); \
        printType(decltype(&magic)(0)); \
    } () \
)

int main(int argc, char **argv) {
    F(1 + 3);
    F(std::cout);
    F(new std::string {"test"});
    F(argv);

    F(int *);
    F(std::string);
    F(char (&&)[5]);
    F(char (&)(int));
    F(decltype(main));

    return 0;
}
