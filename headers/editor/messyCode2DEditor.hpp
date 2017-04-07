#ifndef messyCode2DEditor_hpp
#define messyCode2DEditor_hpp

namespace MessyCode2D_Engine {
    class SceneHierarchy;

    class MessyCode2DEditor
    {
    public:
        MessyCode2DEditor();
        ~MessyCode2DEditor();
        void Update(float deltaTime);
    private:
        SceneHierarchy* hierarchy;
    };
}

#endif
