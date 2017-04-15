#include "messyCode2DEditor.hpp"
#include "scenehierarchy.hpp"

namespace MessyCode2D_Engine {
    MessyCode2DEditor::MessyCode2DEditor()
    {
        this->hierarchy = new SceneHierarchy();
    }

    MessyCode2DEditor::~MessyCode2DEditor()
    {
        delete hierarchy;
        hierarchy = NULL;
    }

    void MessyCode2DEditor::Update()
    {
        hierarchy->Update();
    }
}