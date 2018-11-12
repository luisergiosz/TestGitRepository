#include "SignalSlot.h"

bool SignalSlot::bFinished = false;
bool SignalSlot::bRunning = false;
std::mutex SignalSlot::mutex;

SignalSlot::SignalSlot(std::string class_name)
{
    LOG_3("SignalSlot::SignalSlot() [",class_name,"]");
    s_class_name = class_name;
    std::lock_guard<std::mutex> guard(mutex);
    if(!SignalSlot::bRunning)
    {
        SignalSlot::bRunning = true;
        threadContol = std::thread(SignalSlot::run);
    }

}

SignalSlot::~SignalSlot()
{
    LOG_3("SignalSlot::~SignalSlot() [",s_class_name,"]");
    std::lock_guard<std::mutex> guard(mutex);
    if(SignalSlot::bRunning)
    {
        SignalSlot::bRunning = false;
        if(threadContol.joinable())
            threadContol.join();
        SignalSlot::bFinished = true;
    }
}

void SignalSlot::run()
{
    LOG_3("running signalslot [","","]");
    while(!SignalSlot::bFinished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOG_(".");
    }
    LOG_3("finishing signalslot [","","]");
}
