#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include "scene.hpp"
#include "messyCode2DEditor.hpp"
#include "timer.hpp"

namespace MessyCode2D_Engine {
    class MessyCodeConfig
    {
    public:
        float framePerSec = 30;
    };
    
    class MessyCode2D
    {
    private:
        MessyCodeConfig* config;
        Scene* scene;
        MessyCode2DEditor* editor;
        Timer* timer;
        
        bool ShoulFeed();
        
    public:
        MessyCode2D(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor);
        void Start();
        void Loop();
    };
}
#endif


