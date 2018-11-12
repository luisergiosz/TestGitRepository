#include <iostream>
#include "SignalSlot.h"

using namespace std;

class A : public SignalSlot
{
public:
    A(string class_name):SignalSlot(class_name)
    {
        LOG("A:A()");
    }
    virtual ~A(){LOG("A:~A()");}
    void slot_function()
    {
        cout << "A::slot_function()" << endl;
        emit("slot_function");
    }
};

class B : public SignalSlot
{
public:
    B(string class_name):SignalSlot(class_name)
    {
        LOG("B:B()");
        connect("slot_function",bind(&B::slot_function,this));
    }
    virtual ~B(){LOG("B:~B()");}
    void slot_function()
    {
        cout << "B::slot_function()" << endl;
    }
};

int main()
{
    A a("a");
    B b("b");

    a.slot_function();

    cin.get();
    a.slot_function();
    cin.get();
    a.slot_function();
    cin.get();
    a.slot_function();
    cin.get();
    a.slot_function();


    return 0;
}
