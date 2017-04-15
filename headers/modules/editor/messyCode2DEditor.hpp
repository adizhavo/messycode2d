#ifndef messyCode2DEditor_hpp
#define messyCode2DEditor_hpp

#include <QObject>

namespace MessyCode2D_Engine {
    class SceneHierarchy;

    class MessyCode2DEditor : public QObject
    {
        Q_OBJECT

    public:
        MessyCode2DEditor();
        ~MessyCode2DEditor();

    public slots:
        void Update();

    private:
        SceneHierarchy* hierarchy;
    };
}

#endif
