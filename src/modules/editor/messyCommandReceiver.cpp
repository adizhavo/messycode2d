#include "messyCommandReceiver.hpp"

namespace MessyCode2D_Engine {
    MessyCommandReceiver::MessyCommandReceiver() {
    debugger = MessyCode2D::GetModule<MessyDebugger>();
        if (debugger != NULL)
            debugger->AddReceiver(this);
    }

    MessyCommandReceiver::~MessyCommandReceiver() {
        if (debugger != NULL)
            debugger->RemoveReceiver(this);
    }
}
