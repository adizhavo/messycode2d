#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include "messyCode2DEditor.hpp"
#include "messyCode2DConfig.hpp"
#include "scene.hpp"
#include "timer.hpp"

namespace MessyCode2D_Engine {
    class MessyCode2D
    {
    private:
        MessyCodeConfig* config;
        MessyCode2DEditor* editor;
        Scene* scene;
        Timer* timer;
        
        bool ShoulFeed();
        
    public:
        MessyCode2D(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor);
        void Start();
        void Loop();
    };
}
#endif


