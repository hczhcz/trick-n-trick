#include <iostream>

class Base {
public:
    template <class T>
    T getValue();

    //template <>
    //int getValue<int>();

    virtual void helper() {}
};

class Int: public Base {
private:
    int _val;
public:
    Int(int i): _val(i) {}

    int getInt() {
        return _val;
    }

    virtual void helper() {}
};

template <class T>
T Base::getValue() {
    // cause an error
    T::this_function_call_is_impossible();
};

template <>
int Base::getValue<int>() {
    Int *intobj = dynamic_cast<Int *>(this);

    if (intobj) {
        return intobj->getInt();
    } else {
        throw 233333;
    }
}

int main() {
    using namespace std;

    Base *obj1 = new Int(233);
    Base *obj2 = new Base();

    // ok
    cout << obj1->getValue<int>() << endl;

    // type error
    try {
        cout << obj2->getValue<int>() << endl;
    } catch (...) {
        cout << "obj2 is not an Int obj" << endl;
    }

    // not yet supported
    // cout << obj1->getValue<float>() << endl;

    delete obj1;
    delete obj2;

    return 0;
}
