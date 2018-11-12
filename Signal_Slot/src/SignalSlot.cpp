#include "SignalSlot.h"

bool SignalSlot::bFinished = false;
bool SignalSlot::bRunning = false;
std::mutex SignalSlot::mutex;
std::mutex SignalSlot::mutex_list;
std::multimap<std::string,FuncPtr> SignalSlot::slots;
std::list<std::string> SignalSlot::signals;

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

void SignalSlot::emit(std::string func)
{
    mutex_list.lock();
    signals.push_back(func);
    mutex_list.unlock();
}

void SignalSlot::call_slots()
{
   std::multimap<std::string,FuncPtr>::iterator it;

   while(!signals.empty())
   {
       mutex_list.lock();
       std::string func = signals.front();
       signals.pop_front();
       mutex_list.unlock();

        for(it = slots.begin(); it != slots.end(); ++it)
        {
           if((*it).first == func)
           {
                (*(*it).second)();
           }
        }
   }


}

void SignalSlot::connect(std::string func_name,FuncPtr func)
{
    slots.insert(std::pair<std::string,FuncPtr>(func_name,func));
}

void SignalSlot::run()
{
    LOG_3("running signalslot [","","]");
    while(!SignalSlot::bFinished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //LOG_(".");
        call_slots();
    }
    LOG_3("finishing signalslot [","","]");
}
