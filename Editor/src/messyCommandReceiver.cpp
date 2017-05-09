#include "messyCommandReceiver.hpp"
#include <cstddef>

namespace MessyCode2D_Engine {
    MessyCommandReceiver::MessyCommandReceiver() {
    console = MessyCode2D::GetModule<MessyConsole>();
        if (console != NULL)
            console->AddReceiver(this);
    }

    MessyCommandReceiver::~MessyCommandReceiver() {
        if (console != NULL)
            console->RemoveReceiver(this);
    }
}
