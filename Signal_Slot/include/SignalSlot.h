#ifndef SIGNALSLOT_H
#define SIGNALSLOT_H
#include <thread>
#include <chrono>
#include <mutex>
#include <map>
#include <list>

#include <iostream>

#define LOG_(x)          std::cout << x;
#define LOG(x)          std::cout << x << std::endl;
#define LOG_2(x,y)      std::cout << x << y << std::endl;
#define LOG_3(x,y,z)    std::cout << x << y << z << std::endl;
typedef void (*FuncPtr)();

class SignalSlot
{
    public:
        SignalSlot(std::string class_name);
        virtual ~SignalSlot();

    protected:
        void connect(std::string,FuncPtr);
        static void emit(std::string);

    private:
        static void run();
        static bool bFinished;
        static bool bRunning;
        static std::mutex mutex;
        static std::mutex mutex_list;
        std::thread threadContol;
        std::string s_class_name;
        static std::multimap<std::string,FuncPtr> slots;
        static std::list<std::string> signals;
        static void call_slots();

};

#endif // CSIGNALSLOT_H
