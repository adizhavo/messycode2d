#ifndef MESSY_MODULE
#define MESSY_MODULE

// Every module that wants to use the ServiceLocator of the engine

namespace MessyCode2D_Engine {
    class MessyModule {
      public:
        virtual void Boot() = 0;
        virtual void Start() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual ~MessyModule() { }
    };
}

#endif
