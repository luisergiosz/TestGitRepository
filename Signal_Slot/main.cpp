#include <iostream>
#include "SignalSlot.h"

using namespace std;

class A : public SignalSlot
{
public:
    A(string class_name):SignalSlot(class_name){LOG("A:A()");}
    virtual ~A(){LOG("A:~A()");}

    void slot_function();
    void func_a()
    {
        cout << "aaaaa" << endl;
    }
};

class B : public SignalSlot
{
public:
    B(string class_name):SignalSlot(class_name){LOG("B:B()");}
    virtual ~B(){LOG("B:~B()");}
    void signal_funtion();
};


typedef void (*FuncPtr)();



multimap<string,FuncPtr> slots;

void emit(std::string func)
{
   multimap<string,FuncPtr>::iterator it;
   for(it = slots.begin(); it != slots.end(); ++it)
   {
       if((*it).first == func)
       {
            (*(*it).second)();
       }
   }
}
int main()
{
    A a("a");
    B b("b");


    slots.insert(std::pair<string,FuncPtr>("func_a",a.func_a));
    emit("func_a");

    cin.get();
    return 0;
}
