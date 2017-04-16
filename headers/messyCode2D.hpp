#ifndef messyCode2D_hpp
#define messyCode2D_hpp

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "messyModule.hpp"
#if MESSY_LOGS
#include <iostream>
#endif

namespace MessyCode2D_Engine {
    class MessyCode2D : public QObject
    {
        Q_OBJECT

    private:
        std::vector<MessyModule*> modules;
        QElapsedTimer* elapseTimer;
        QTimer* timer;
        
    public:
        static MessyCode2D* instance;
        void AddService(MessyModule* module);
        void Boot();
        void Start();

        MessyCode2D();
        ~MessyCode2D();

        template<typename T> T* GetModule() {
                   for (MessyModule* module : modules) {
                       T* m = dynamic_cast<T*>(module);
                       if (m != NULL)
                           return m;
                   }
#if MESSY_LOGS
                    std::count << "module requested was not found, return null";
#endif
                   return NULL;
               }

    public slots:
        void Update();
    };
}
#endif


