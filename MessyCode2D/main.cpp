#include <iostream>
#include "messyCode2D.hpp"
#include "scene.hpp"
#include "messyCode2DEditor.hpp"
#include "messyCode2DConfig.hpp"

using namespace MessyCode2D_Engine;

int main(int argc, const char * argv[]) {
    
    MessyCodeConfig config;
    
    Scene scene;
    scene.Build();
    
    MessyCode2DEditor editor;
    
    MessyCode2D* engine = new MessyCode2D(&config, &scene, &editor);
    
    engine->Start();
    engine->Loop();
    
    return 0;
}
