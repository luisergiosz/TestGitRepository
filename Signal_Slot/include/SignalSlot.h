#ifndef SIGNALSLOT_H
#define SIGNALSLOT_H
#include <thread>
#include <chrono>
#include <mutex>
#include <map>

#include <iostream>

#define LOG_(x)          std::cout << x;
#define LOG(x)          std::cout << x << std::endl;
#define LOG_2(x,y)      std::cout << x << y << std::endl;
#define LOG_3(x,y,z)    std::cout << x << y << z << std::endl;

class SignalSlot;



class SignalSlot
{
    public:
        SignalSlot(std::string class_name);
        virtual ~SignalSlot();

    protected:

    private:
        static void run();
        static bool bFinished;
        static bool bRunning;
        static std::mutex mutex;
        std::thread threadContol;
        std::string s_class_name;
};

#endif // CSIGNALSLOT_H
