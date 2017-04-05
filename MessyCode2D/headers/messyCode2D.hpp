#ifndef messyCode2D_hpp
#define messyCode2D_hpp

namespace MessyCode2D_Engine {
    class MessyCodeConfig;
    class MessyCode2DEditor;
    class Scene;
    class Timer;
    
    class MessyCode2D
    {
    private:
        MessyCodeConfig* config;
        MessyCode2DEditor* editor;
        Scene* scene;
        Timer* timer;
        
        bool ShouldUpdate();
        
    public:
        MessyCode2D(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor);
        void Start();
        void Loop();
    };
}
#endif


