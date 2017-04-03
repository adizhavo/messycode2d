#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include "scene.hpp"
#include "messyCode2DEditor.hpp"

namespace MessyCode2D_Engine {
    class MessyCode2D
    {
    private:
        Scene *scene;
        MessyCode2DEditor* editor;
        
    public:
        MessyCode2D(Scene* scene, MessyCode2DEditor* editor);
        void Boot();
        void Loop();
    };
}
#endif


