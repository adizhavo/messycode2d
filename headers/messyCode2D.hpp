#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

namespace MessyCode2D_Engine {
    class MessyCodeConfig;
    class MessyCode2DEditor;
    class Scene;
    
    class MessyCode2D : public QObject
    {
        Q_OBJECT

    private:
        MessyCodeConfig* config;
        MessyCode2DEditor* editor;
        Scene* scene;
        QTimer* timer;
        QElapsedTimer* elapseTimer;
        
    public:
        void Boot(MessyCodeConfig* config, Scene* scene, MessyCode2DEditor* editor);
        void Start();

        ~MessyCode2D();

    public slots:
        void Loop();
    };
}
#endif


