#ifndef MESSYCOMMANDRECEIVER_H
#define MESSYCOMMANDRECEIVER_H

#include "messyCode2D.hpp"
#include "messyDebugger.hpp"

namespace MessyCode2D_Engine {
    // Inherit to receive commands form the Editor console

    class MessyCommandReceiver
    {
    private:
        MessyDebugger* debugger = 0;

    public:
        MessyCommandReceiver();
       ~MessyCommandReceiver();
        virtual void ReceiveCommand(std::string const command) = 0;
    };
}

#endif // MESSYCOMMANDRECEIVER_H
