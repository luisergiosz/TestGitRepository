#ifndef CONTROLSIGNALSLOT_H
#define CONTROLSIGNALSLOT_H
#include <thread>

class ControlSignalSlot
{
    public:
        ControlSignalSlot();
        virtual ~ControlSignalSlot();

    protected:

    private:
        void run();
};

#endif // CONTROLSIGNALSLOT_H
