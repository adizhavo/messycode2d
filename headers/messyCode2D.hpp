#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "messyModule.hpp"

namespace MessyCode2D_Engine {
    class MessyCode2D : public QObject
    {
        Q_OBJECT

    private:
        static std::vector<MessyModule*> modules;
        QElapsedTimer* elapseTimer;
        QTimer* timer;

    public:
        void Boot();
        void Start();

        MessyCode2D();
        ~MessyCode2D();

        static void AddModule(MessyModule* module);
        template<typename T> static T* GetModule() {
            for (MessyModule* module : modules) {
               T* m = dynamic_cast<T*>(module);
               if (m != NULL)
                  return m;
               }
            return NULL;
        }

    public slots:
        void Update();
    };
}
#endif


