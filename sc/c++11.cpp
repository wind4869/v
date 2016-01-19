#include <iostream>
#include <vector>
#include <map>
using namespace std;

void lambda_test()
{
    char s[] = "Hello World!";
    int Uppercase = 0;
    for_each(s, s + sizeof(s), [&Uppercase](char c) {
        if (isupper(c))
            Uppercase++;
    });
    cout << Uppercase << " uppercase letters in: " << s << endl;
}

void auto_test()
{
    vector<int> v = {5, 3, 4, 1, 2};
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    for (auto it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

void initialize_test()
{
    int *a = new int[3] {1, 2, 3}; // C++11 only

    class X {
        int a[4];
    public:
        X() : a{1, 2, 3, 4} {} // C++11 only
    };

    vector<string> vs = {"first", "second", "third"};
    map<string, string> singers = {
            {"Lady Gaga", "+1 (212) 555-7890"},
            {"Beyonce Knowles", "+1 (212) 555-0987"}
    };

    class C {
        int a = 7; // C++11 only
    public:
        C() {};
    };
}

template <typename LHS, typename RHS>
auto AddingFunc(const LHS &lhs, const RHS & rhs) -> decltype(lhs + rhs)
{ return lhs + rhs; }

struct A {
    A()=default; // C++11
    virtual ~A()=default; // C++11
};

struct NoCopy {
    NoCopy()=default;
    NoCopy(const NoCopy &)=delete;
    NoCopy & operator=(const NoCopy &)=delete;
};

void f(int) { cout << "int" << endl; };
void f(char *) { cout << "char *" << endl; };

class SomeType {
    int number;
    string name;
    SomeType(int i, string s) : number(i), name(s) {}
public:
    SomeType() : SomeType(0, "invalid") {}
    SomeType(int i) : SomeType(i, "guest") {}
    SomeType(string s) : SomeType(1, s) {}
};

class BaseClass {
public:
    BaseClass()=default;
    BaseClass(int i) { cout << "BaseClass(int i)" << endl; };
};

class DerivedClass : public BaseClass {
public:
    using BaseClass::BaseClass;
    DerivedClass() : BaseClass(1) {}
};

int main()
{
    lambda_test();
    auto_test();
    initialize_test();
    cout << AddingFunc(1, 3.1) << endl;
    NoCopy a;
//    NoCopy b(a); // error
//    NoCopy b = a; // error
    f(0);
    f(nullptr); // C++11
    DerivedClass d;
    return 0;
}